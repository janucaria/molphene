#include "stdafx.hpp"

#include "Scene.hpp"
#include "m3d.hpp"
#include "shape/UvSphere.hpp"

namespace molphene {

bool
Scene::setup_graphics()
{
  material_.diffuse_color = 0xFFFFFF;

  point_light_source_.location = {0, 0, -23};
  point_light_source_.radius = 5;

  spot_light_source_.location = {0, 0, -20};

  camera_.projection_mode(true);

  return true;
}

void
Scene::change_dimension(GLsizei width, GLsizei height)
{
  camera_.set_resolution(width, height);
  calculate_matrices();
}

void
Scene::reset_mesh()
{
  std::vector<Atom*> atoms;
  std::vector<Bond*> bonds;

  for(auto& model : Molecule::Models_iterable{*molecule_}) {
    for(auto& chain : Model::Chains_iterable{model}) {
      for(auto& residue : Chain::Residue_iterator{chain}) {
        for(auto& atom : Compound::Atoms_iterable{residue}) {
          const auto atm = std::addressof(atom);
          atoms.push_back(atm);
        }
      }

      for(auto& ligan : Chain::Ligan_iterator{chain}) {
        const auto compname = ligan.name();
        for(auto& atom : Compound::Atoms_iterable{ligan}) {
          const auto atm = std::addressof(atom);
          atoms.push_back(atm);
        }
      }
    }

    for(auto& bond : Model::Bonds_iterable{model}) {
      bonds.push_back(&bond);
    }
  }

  // calculate bounding sphere
  auto bs = BoundingSphere<float_t>{};

  for(auto& model : Molecule::Models_iterable{*molecule_}) {
    for(auto& chain : Model::Chains_iterable{model}) {
      for(auto& residue : Chain::Compound_iterator{chain}) {
        for(auto& atom : Compound::Atoms_iterable{residue}) {
          bs.expand(Vec3f(atom.position()));
        }
      }
    }
  }

  camera_.top = bs.radius() + 2;
  model_matrix_.identity().translate(-bs.center());

  calculate_matrices();

  constexpr auto max_chunk_bytes = size_t{1024 * 1024 * 128};
  auto mesh_builder = SphereMeshBuilder{max_chunk_bytes, 10, 20};

  const auto total_instances = atoms.size();
  const auto vertices_per_instance = mesh_builder.get_vertices_size();
  const auto model_per_chunks = mesh_builder.size();
  const auto remain_models = total_instances % model_per_chunks;

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

    mesh_builder.sphere(UvSphere<float_t>{arad, apos});

    mesh_builder.texcoord(atex);

    const auto j = i % model_per_chunks;
    mesh_builder.build(j);
    if(j == (model_per_chunks - 1)) {
      sphere_buff_atoms_->set_data(chunk_count * model_per_chunks,
                                   model_per_chunks,
                                   mesh_builder.positions(),
                                   mesh_builder.normals(),
                                   mesh_builder.texcoords());
      ++chunk_count;
    }
  }

  if(remain_models > 0) {
    sphere_buff_atoms_->set_data(chunk_count * model_per_chunks,
                                 remain_models,
                                 mesh_builder.positions(),
                                 mesh_builder.normals(),
                                 mesh_builder.texcoords());
  }

  sphere_buff_atoms_->color_texture_image_data(colors.data());
}

void
Scene::rotate(Scene::Vec3f rot)
{
  const auto [x, y, z] = rot;
  model_matrix_.rotate(1.0f, 0.0f, 0.0f, x);
  model_matrix_.rotate(0.0f, 1.0f, 0.0f, y);
  model_matrix_.rotate(0.0f, 0.0f, 1.0f, z);
}

void
Scene::calculate_matrices()
{
  const auto fov = camera_.fov;
  const auto top = camera_.top;
  const auto aspect = camera_.aspect_ratio();
  const auto tan_theta = tan(fov / 2);
  const auto focal_len = [=]() {
    auto focal = top / tan_theta;
    if(aspect < 1) {
      focal /= aspect;
    }
    return focal;
  }();

  camera_.near = focal_len - top;
  camera_.far = focal_len + top;

  camera_.view_matrix.set_translate(0, 0, -focal_len);
}

void
Scene::open_stream(std::istream& is)
{
  molecule_ = std::make_unique<Molecule>();
  PdbParser parser;
  parser.parse(molecule_.get(), is);
}

typename Scene::Camera&
Scene::get_camera()
{
  return camera_;
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


} // namespace molphene
