#include "stdafx.hpp"

#include "ColourManager.hpp"
#include "ExpandIterator.hpp"
#include "Scene.hpp"
#include "algorithm.hpp"
#include "m3d.hpp"
#include "mol/AtomInsertIterator.hpp"
#include "mol/BondInsertIterator.hpp"
#include "shape/Cylinder.hpp"
#include "shape/Sphere.hpp"

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

  auto atoms = std::vector<const Atom*>{};
  auto bonds = std::vector<const Bond*>{};
  using pair_atoms_t = std::pair<const Atom*, const Atom*>;
  auto bond_atoms = std::vector<pair_atoms_t>{};
  auto atoms_in_bond = std::vector<const Atom*>{};

  bonds.reserve(molecule_.bonds().size());
  range::transform(
   molecule_.bonds(), std::back_inserter(bonds), [](auto& bond) noexcept {
     return std::addressof(bond);
   });

  bond_atoms.reserve(bonds.size());
  range::transform(
   bonds,
   std::back_inserter(bond_atoms),
   [& atoms = molecule_.atoms()](auto bond_ptr) noexcept {
     return std::make_pair(&atoms.at(bond_ptr->atom1()),
                           &atoms.at(bond_ptr->atom2()));
   });

  atoms.reserve(molecule_.atoms().size());
  range::transform(
   molecule_.atoms(), std::back_inserter(atoms), [](auto& atom) noexcept {
     return &atom;
   });

  atoms_in_bond.reserve(atoms.size());
  boost::algorithm::copy_if(
   atoms, std::back_inserter(atoms_in_bond), [&](auto* atom) {
     return boost::find_if(bond_atoms, [&](auto atom_pair) {
              return atom == atom_pair.first || atom == atom_pair.second;
            }) != std::end(bond_atoms);
   });
  atoms_in_bond.shrink_to_fit();

  // calculate bounding sphere
  bounding_sphere_.reset();

  range::transform(
   atoms, ExpandIterator{bounding_sphere_}, [](auto atom) noexcept {
     return atom->position();
   });

  model_matrix_.identity().translate(-bounding_sphere_.center());

  {
    auto sphere_mesh_attrs = std::vector<SphereMeshAttr>{};
    sphere_mesh_attrs.reserve(atoms.size());

    transform_sphere_attrs(
     spacefill_representation_, atoms, std::back_inserter(sphere_mesh_attrs));

    spacefill_representation_.atom_sphere_buffer =
     build_sphere_mesh(sphere_mesh_attrs);
  }

  {
    {
      auto sphere_mesh_attrs = std::vector<SphereMeshAttr>{};
      sphere_mesh_attrs.reserve(atoms_in_bond.size());

      transform_sphere_attrs(ballnstick_representation_,
                             atoms_in_bond,
                             std::back_inserter(sphere_mesh_attrs));

      ballnstick_representation_.atom_sphere_buffer =
       build_sphere_mesh(sphere_mesh_attrs);
    }

    auto cylinder_mesh_attrs = std::vector<CylinderMeshAttr>{};
    cylinder_mesh_attrs.reserve(bond_atoms.size());

    transform_clylinder_attrs(true,
                              ballnstick_representation_,
                              bond_atoms,
                              std::back_insert_iterator(cylinder_mesh_attrs));
    ballnstick_representation_.bond1_cylinder_buffer =
     build_cylinder_mesh(cylinder_mesh_attrs);

    cylinder_mesh_attrs.clear();

    transform_clylinder_attrs(false,
                              ballnstick_representation_,
                              bond_atoms,
                              std::back_insert_iterator(cylinder_mesh_attrs));
    ballnstick_representation_.bond2_cylinder_buffer =
     build_cylinder_mesh(cylinder_mesh_attrs);
  }
}

auto Scene::build_sphere_mesh(const std::vector<SphereMeshAttr>& sph_attrs)
 -> std::unique_ptr<ColorLightBuffer>
{
  const auto total_instances = sph_attrs.size();
  auto mesh_builder = SphereMeshBuilder{10, 20};
  const auto vertices_per_instance = mesh_builder.vertices_size();

  auto sphere_buff_atoms =
   new ColorLightBuffer(vertices_per_instance, total_instances);

  constexpr auto max_chunk_bytes = size_t{1024 * 1024 * 128};
  constexpr auto bytes_per_vertex =
   sizeof(Vec3<GLfloat>) + sizeof(Vec3<GLfloat>) + sizeof(Vec2<GLfloat>);
  const auto bytes_per_instance = bytes_per_vertex * vertices_per_instance;
  const auto max_models =
   bytes_per_instance ? max_chunk_bytes / bytes_per_instance : 0;
  const auto instances_per_chunk = std::min(total_instances, max_models);
  const auto vertices_per_chunk = instances_per_chunk * vertices_per_instance;

  const auto tex_size = sphere_buff_atoms->color_texture_size();
  auto colors = std::vector<Rgba8>{};
  colors.reserve(tex_size * tex_size);

  auto chunk_count = size_t{0};
  for_each_slice(sph_attrs, instances_per_chunk, [&](auto sph_attrs_range) {
    const auto instances_size = boost::distance(sph_attrs_range);

    auto normals = std::vector<Vec3<GLfloat>>{};
    auto positions = std::vector<Vec3<GLfloat>>{};
    auto texcoords = std::vector<Vec2<GLfloat>>{};

    positions.reserve(vertices_per_chunk);
    normals.reserve(vertices_per_chunk);
    texcoords.reserve(vertices_per_chunk);
    for(const auto& sph_attr : sph_attrs_range) {
      const auto acol = sph_attr.color;
      const auto atex = sph_attr.texcoord;
      const auto sph = sph_attr.sphere;

      colors.push_back(acol);

      mesh_builder.build_positions(sph, std::back_inserter(positions));
      mesh_builder.build_normals(std::back_inserter(normals));
      mesh_builder.build_texcoords(atex, std::back_inserter(texcoords));
    }

    sphere_buff_atoms->set_data(chunk_count * instances_per_chunk,
                                instances_size,
                                positions,
                                normals,
                                texcoords);
    ++chunk_count;
  });

  colors.resize(colors.capacity());
  sphere_buff_atoms->color_texture_image_data(colors.data());

  return std::unique_ptr<ColorLightBuffer>{sphere_buff_atoms};
}

auto Scene::build_cylinder_mesh(const std::vector<CylinderMeshAttr>& cyl_attrs)
 -> std::unique_ptr<ColorLightBuffer>
{
  const auto total_instances = cyl_attrs.size();
  auto mesh_builder = CylinderMeshBuilder{20};
  const auto vertices_per_instance = mesh_builder.vertices_size();

  auto cyl_buff_bonds =
   new ColorLightBuffer(vertices_per_instance, total_instances);

  constexpr auto max_chunk_bytes = size_t{1024 * 1024 * 128};
  constexpr auto bytes_per_vertex =
   sizeof(Vec3<GLfloat>) + sizeof(Vec3<GLfloat>) + sizeof(Vec2<GLfloat>);
  const auto bytes_per_instance = bytes_per_vertex * vertices_per_instance;
  const auto max_models =
   bytes_per_instance ? max_chunk_bytes / bytes_per_instance : 0;
  const auto instances_per_chunk = std::min(total_instances, max_models);
  const auto vertices_per_chunk = instances_per_chunk * vertices_per_instance;

  const auto tex_size = cyl_buff_bonds->color_texture_size();
  auto colors = std::vector<Rgba8>{};
  colors.reserve(tex_size * tex_size);

  auto chunk_count = size_t{0};
  for_each_slice(cyl_attrs, instances_per_chunk, [&](auto cyl_attrs_range) {
    const auto instances_size = boost::distance(cyl_attrs_range);

    auto normals = std::vector<Vec3<GLfloat>>{};
    auto positions = std::vector<Vec3<GLfloat>>{};
    auto texcoords = std::vector<Vec2<GLfloat>>{};

    positions.reserve(vertices_per_chunk);
    normals.reserve(vertices_per_chunk);
    texcoords.reserve(vertices_per_chunk);

    for(const auto& cyl_attr : cyl_attrs_range) {
      const auto acol = cyl_attr.color;
      const auto atex = cyl_attr.texcoord;
      const auto cyl = cyl_attr.cylinder;

      colors.push_back(acol);

      mesh_builder.build_positions(cyl, std::back_inserter(positions));
      mesh_builder.build_normals(cyl, std::back_inserter(normals));
      mesh_builder.build_texcoords(cyl, atex, std::back_inserter(texcoords));
    }

    cyl_buff_bonds->set_data(chunk_count * instances_per_chunk,
                             instances_size,
                             positions,
                             normals,
                             texcoords);
    ++chunk_count;
  });

  colors.resize(colors.capacity());
  cyl_buff_bonds->color_texture_image_data(colors.data());

  return std::unique_ptr<ColorLightBuffer>{cyl_buff_bonds};
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

  auto jsonmol = nlohmann::json::parse(strjson);

  auto find_object_json_by_key =
   [](const auto& jsonmol,
      const std::string& key) -> std::optional<nlohmann::json::object_t> {
    const auto find_key = jsonmol.find(key);
    if(find_key == jsonmol.end()) {
      return std::nullopt;
    }

    const auto json_value = *find_key;

    if(!json_value.is_object()) {
      return std::nullopt;
    }

    return json_value;
  };

  auto pdb_json = find_object_json_by_key(jsonmol, "mol");
  if(pdb_json) {
    jsonmol = *pdb_json;
  }

  auto out_atoms = AtomInsertIterator{molecule};
  auto out_bonds = BondInsertIterator{molecule};

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

    boost::range::transform(*json_atoms, outiter, [](auto const json_atom) {
      auto const aelement = json_atom.template value<std::string>("l", "C");
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

    boost::range::transform(*json_bonds, outiter, [](auto const json_bond) {
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
  return spacefill_representation_.atom_sphere_buffer.get();
}

auto Scene::cyl_bond1_mesh_buffers() const noexcept -> const ColorLightBuffer*
{
  return ballnstick_representation_.bond1_cylinder_buffer.get();
}

auto Scene::cyl_bond2_mesh_buffers() const noexcept -> const ColorLightBuffer*
{
  return ballnstick_representation_.bond2_cylinder_buffer.get();
}

auto Scene::ballnstick_sphere_atom_buffers() const noexcept
 -> const ColorLightBuffer*
{
  return ballnstick_representation_.atom_sphere_buffer.get();
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
