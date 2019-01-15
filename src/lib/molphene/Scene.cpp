#include "stdafx.hpp"

#include "ExpandIterator.hpp"
#include "Scene.hpp"
#include "algorithm.hpp"
#include "m3d.hpp"
#include "mol/AtomInsertIterator.hpp"
#include "mol/BondInsertIterator.hpp"
#include "shape/UvSphere.hpp"

namespace molphene {

auto Scene::setup_graphics() noexcept -> bool
{
  material_.diffuse_color = {0xFF, 0xFF, 0xFF};

  point_light_source_.location = {0, 0, -23};
  point_light_source_.radius = 5;

  spot_light_source_.location = {0, 0, -20};

  return true;
}

void Scene::reset_mesh() noexcept
{
  namespace range = boost::range;

  std::vector<Atom*> atoms;
  atoms.reserve(molecule_.atoms().size());

  std::transform(std::begin(molecule_.atoms()),
                 std::end(molecule_.atoms()),
                 std::back_inserter(atoms),
                 [](auto& atom) { return std::addressof(atom); });

  // calculate bounding sphere
  bounding_sphere_.reset();

  range::transform(
   atoms, ExpandIterator{bounding_sphere_}, [](auto atom) noexcept {
     return atom->position();
   });

  model_matrix_.identity().translate(-bounding_sphere_.center());

  const auto total_instances = atoms.size();

  constexpr auto max_chunk_bytes = size_t{1024 * 1024 * 128};

  {
    auto mesh_builder = SphereMeshBuilder{10, 20};

    constexpr auto bytes_per_vertex =
     sizeof(Vec3<GLfloat>) + sizeof(Vec3<GLfloat>) + sizeof(Vec2<GLfloat>);

    const auto vertices_per_instance = mesh_builder.vertices_size();
    const auto bytes_per_instance = bytes_per_vertex * vertices_per_instance;
    const auto max_models =
     bytes_per_instance ? max_chunk_bytes / bytes_per_instance : 0;
    const auto instances_per_chunk = std::min(total_instances, max_models);
    const auto vertices_per_chunk = instances_per_chunk * vertices_per_instance;

    sphere_buff_atoms_ =
     std::make_unique<typename decltype(sphere_buff_atoms_)::element_type>(
      vertices_per_instance, total_instances);

    const auto tex_size = sphere_buff_atoms_->color_texture_size();
    auto colors = std::vector<Rgba8>(tex_size * tex_size);

    auto chunk_count = size_t{0};
    auto instance_i = size_t{0};
    for_each_slice(
     std::begin(atoms),
     std::end(atoms),
     instances_per_chunk,
     [&](auto atoms_begin, auto atoms_end) {
       const auto instances_size = std::distance(atoms_begin, atoms_end);

       auto normals = std::vector<Vec3<GLfloat>>{};
       auto positions = std::vector<Vec3<GLfloat>>{};
       auto texcoords = std::vector<Vec2<GLfloat>>{};

       positions.reserve(vertices_per_chunk);
       normals.reserve(vertices_per_chunk);
       texcoords.reserve(vertices_per_chunk);
       for(; atoms_begin != atoms_end; ++atoms_begin) {
         const auto& atom = **atoms_begin;
         const auto element = atom.element();
         const auto apos = atom.position();
         const auto arad = element.rvdw;
         const auto acol = colour_manager_.get_element_color(element.symbol);
         const auto atex =
          Vec2f{float_type(instance_i % tex_size) / tex_size,
                std::floorf(float_type(instance_i) / tex_size) / tex_size};

         colors[instance_i] = acol;

         mesh_builder.build_positions(
          apos, arad, std::back_inserter(positions));
         mesh_builder.build_normals(std::back_inserter(normals));
         mesh_builder.build_texcoords(atex, std::back_inserter(texcoords));

         ++instance_i;
       }

       sphere_buff_atoms_->set_data(chunk_count * instances_per_chunk,
                                    instances_size,
                                    positions,
                                    normals,
                                    texcoords);
       ++chunk_count;
     });

    sphere_buff_atoms_->color_texture_image_data(colors.data());
  }
}

void Scene::rotate(Scene::Vec3f rot) noexcept
{
  model_matrix_.rotate(rot.x(), {1.0f, 0.0f, 0.0f});
  model_matrix_.rotate(rot.y(), {0.0f, 1.0f, 0.0f});
  model_matrix_.rotate(rot.z(), {0.0f, 0.0f, 1.0f});
}

void Scene::open_chemdoodle_json_stream(std::istream& is)
{
  const auto strjson = std::string{std::istreambuf_iterator<char>{is}, {}};
  molecule_ = parse_chemdoodle_json(strjson);
}

auto Scene::parse_chemdoodle_json(const std::string& strjson) -> Molecule
{
  auto molecule = Molecule{};
  if(strjson.empty()) {
    return molecule;
  }

  auto out_atoms = AtomInsertIterator{molecule};
  auto out_bonds = BondInsertIterator{molecule};

  const auto jsonmol = nlohmann::json::parse(strjson);

  auto find_array_json_by_key =
   [](const auto& jsonmol,
      const std::string& key) -> std::optional<nlohmann::json::array_t> {
    const auto find_array = jsonmol.find(key);
    if(find_array == jsonmol.end()) {
      return std::nullopt;
    }

    const auto json_array = *find_array;

    if(!json_array.is_array()) {
      return std::nullopt;
    }

    return json_array;
  };

  [find_array_json_by_key](const auto& jsonmol, auto outiter) {
    const auto json_atoms = find_array_json_by_key(jsonmol, "a");
    if(!json_atoms) {
      return;
    }

    std::transform(std::begin(*json_atoms),
                   std::end(*json_atoms),
                   outiter,
                   [](auto const json_atom) {
                     auto const aelement =
                      json_atom.template value<std::string>("l", "C");
                     auto const ax = json_atom.template value<double>("x", 0);
                     auto const ay = json_atom.template value<double>("y", 0);
                     auto const az = json_atom.template value<double>("z", 0);

                     auto atom = Atom{aelement, "", 0};
                     atom.position(ax, ay, az);

                     return atom;
                   });
  }(jsonmol, out_atoms);

  [find_array_json_by_key](const auto& jsonmol, auto outiter) {
    const auto json_bonds = find_array_json_by_key(jsonmol, "b");
    if(!json_bonds) {
      return;
    }

    std::transform(std::begin(*json_bonds),
                   std::end(*json_bonds),
                   outiter,
                   [](auto const json_bond) {
                     auto const ibegin = static_cast<int>(json_bond.at("b"));
                     auto const iend = static_cast<int>(json_bond.at("e"));

                     auto bond = Bond{ibegin, iend};

                     return bond;
                   });
  }(jsonmol, out_bonds);

  return molecule;
}

auto Scene::model_matrix() const noexcept -> Mat4f
{
  return model_matrix_;
}

auto Scene::light_source() const noexcept -> LightSource
{
  return light_source_;
}

auto Scene::material() const noexcept -> Material
{
  return material_;
}

auto Scene::fog() const noexcept -> Fog
{
  return fog_;
}

auto Scene::mesh_buffers() const noexcept -> const ColorLightBuffer*
{
  return sphere_buff_atoms_.get();
}

void Scene::change_dimension(size_type width, size_type height) noexcept
{
  viewport_.width = width;
  viewport_.height = height;
}

auto Scene::viewport() const noexcept -> Viewport
{
  return viewport_;
}

auto Scene::bounding_sphere() const noexcept -> BoundingSphere
{
  return bounding_sphere_;
}

} // namespace molphene
