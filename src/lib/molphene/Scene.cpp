#include "stdafx.hpp"

#include "ExpandIterator.hpp"
#include "Scene.hpp"
#include "m3d.hpp"
#include "shape/UvSphere.hpp"

namespace molphene {

bool
Scene::setup_graphics() noexcept
{
  material_.diffuse_color = {0xFF, 0xFF, 0xFF};

  point_light_source_.location = {0, 0, -23};
  point_light_source_.radius = 5;

  spot_light_source_.location = {0, 0, -20};

  return true;
}

void
Scene::reset_mesh() noexcept
{
  namespace range = boost::range;

  std::vector<Atom*> atoms;
  std::vector<Bond*> bonds;

  for(auto& model : Molecule::ModelsIterable{*molecule_}) {
    for(auto& chain : Model::ChainsIterable{model}) {
      for(auto& residue : Chain::ResidueIterator{chain}) {
        for(auto& atom : Compound::AtomsIterable{residue}) {
          const auto atm = std::addressof(atom);
          atoms.push_back(atm);
        }
      }

      for(auto& ligan : Chain::LiganIterator{chain}) {
        const auto compname = ligan.name();
        for(auto& atom : Compound::AtomsIterable{ligan}) {
          const auto atm = std::addressof(atom);
          atoms.push_back(atm);
        }
      }
    }

    for(auto& bond : Model::BondsIterable{model}) {
      bonds.push_back(&bond);
    }
  }

  // calculate bounding sphere
  bounding_sphere_.reset();

  range::transform(atoms, ExpandIterator{bounding_sphere_}, [
  ](auto atom) noexcept { return atom->position(); });

  model_matrix_.identity().translate(-bounding_sphere_.center());

  const auto total_instances = atoms.size();

  constexpr auto max_chunk_bytes = size_t{1024 * 1024 * 128};

  {
    auto normals = std::vector<Vec3<GLfloat>>{};
    auto positions = std::vector<Vec3<GLfloat>>{};
    auto texcoords = std::vector<Vec2<GLfloat>>{};

    auto mesh_builder = SphereMeshBuilder{10, 20};

    constexpr auto bytes_per_vertex =
     sizeof(typename std::decay_t<decltype(positions)>::value_type) +
     sizeof(typename std::decay_t<decltype(normals)>::value_type) +
     sizeof(typename std::decay_t<decltype(texcoords)>::value_type);

    const auto vertices_per_instance = mesh_builder.vertices_size();
    const auto bytes_per_instance = bytes_per_vertex * vertices_per_instance;
    const auto max_models = max_chunk_bytes / bytes_per_instance;
    const auto instances_per_chunk = std::min(total_instances, max_models);
    const auto vertices_per_chunk = instances_per_chunk * vertices_per_instance;
    const auto remain_instances = total_instances % instances_per_chunk;

    positions.reserve(vertices_per_chunk);
    normals.reserve(vertices_per_chunk);
    texcoords.reserve(vertices_per_chunk);

    sphere_buff_atoms_ =
     std::make_unique<typename decltype(sphere_buff_atoms_)::element_type>(
      vertices_per_instance, total_instances);

    const auto tex_size = sphere_buff_atoms_->color_texture_size();
    auto colors = std::vector<Rgba8>(tex_size * tex_size);

    auto chunk_count = size_t{0};
    for(auto i = size_t{0}; i < total_instances; ++i) {
      const auto& atm = *atoms.at(i);
      const auto& element = atm.element();
      const auto apos = atm.position();
      const auto arad = element.rvdw;
      const auto acol = colour_manager_.get_element_color(element.symbol);
      const auto atex = Vec2f{float_t(i % tex_size) / tex_size,
                              std::floorf(float_t(i) / tex_size) / tex_size};
      colors[i] = acol;

      auto spherenorms = std::vector<Vec3f>{};
      spherenorms.reserve(vertices_per_instance);

      mesh_builder.build(std::back_inserter(spherenorms));

      range::copy(spherenorms, std::back_inserter(normals));
      range::transform(
       spherenorms, std::back_inserter(positions), [=](auto norm) noexcept {
         return apos + norm * arad;
       });
      std::fill_n(std::back_inserter(texcoords), spherenorms.size(), atex);

      if(positions.size() == vertices_per_chunk) {
        sphere_buff_atoms_->set_data(chunk_count * instances_per_chunk,
                                     instances_per_chunk,
                                     positions,
                                     normals,
                                     texcoords);
        ++chunk_count;

        positions.clear();
        normals.clear();
        texcoords.clear();
      }
    }

    if(remain_instances > 0) {
      sphere_buff_atoms_->set_data(chunk_count * instances_per_chunk,
                                   remain_instances,
                                   positions,
                                   normals,
                                   texcoords);
    }

    sphere_buff_atoms_->color_texture_image_data(colors.data());
  }
}

void
Scene::rotate(Scene::Vec3f rot) noexcept
{
  model_matrix_.rotate(rot.x(), {1.0f, 0.0f, 0.0f});
  model_matrix_.rotate(rot.y(), {0.0f, 1.0f, 0.0f});
  model_matrix_.rotate(rot.z(), {0.0f, 0.0f, 1.0f});
}

void
Scene::open_stream(std::istream& is)
{
  molecule_ = std::make_unique<Molecule>();
  PdbParser parser;
  parser.parse(molecule_.get(), is);
}

typename Scene::Mat4f
Scene::model_matrix() const noexcept
{
  return model_matrix_;
}

typename Scene::LightSource
Scene::light_source() const noexcept
{
  return light_source_;
}

typename Scene::Material
Scene::material() const noexcept
{
  return material_;
}

typename Scene::Fog
Scene::fog() const noexcept
{
  return fog_;
}

const ColorLightBuffer*
Scene::mesh_buffers() const noexcept
{
  return sphere_buff_atoms_.get();
}

void
Scene::change_dimension(size_t width, size_t height) noexcept
{
  viewport_.width = width;
  viewport_.height = height;
}

auto
Scene::viewport() const noexcept -> Viewport
{
  return viewport_;
}

auto
Scene::bounding_sphere() const noexcept -> BoundingSphere
{
  return bounding_sphere_;
}

} // namespace molphene
