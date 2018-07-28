#include "Scene.hpp"
#include "m3d.hpp"
#include "shape/Sphere.hpp"
#include "sphere_data.h"

namespace molphene {

bool
Scene::setup_graphics()
{
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glEnable(GL_DEPTH_TEST);

  light_source_.ambient = 0x7F7F7Fu;
  light_source_.diffuse = 0xFFFFFFu;
  light_source_.specular = 0x7F7F7Fu;
  light_source_.direction = {0.0, 0.0, 0.0};

  material_.ambient = 0x4C4C4Cu;
  material_.diffuse = 0xFFFFFFu;
  material_.specular = 0x7F7F7Fu;
  material_.shininess = 10;

  camera_.projection_mode(true);

  color_light_shader_.init_program();
  color_light_shader_.use_program();
  color_light_shader_.light_source(light_source_);
  color_light_shader_.material(material_);

  sphere_buff_atoms_.setup();

  return true;
}

void
Scene::change_dimension(GLsizei width, GLsizei height)
{
  camera_.set_resolution(width, height);
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

  calculate_matrices();

  sphere_data spheredat;

  const auto total_atoms = static_cast<GLuint>(atoms.size());
  const auto total_vertices = total_atoms * spheredat.unitlen();

  spheredat.reserve(total_atoms);
  sphere_buff_atoms_.reserve(total_vertices);
  for(const auto atom : atoms) {
    const auto& atm = *atom;
    const auto element = atm.element();
    const auto apos = atm.position();
    const auto arad = element.rvdw;
    const auto acol = colour_manager_.get_element_color(element.symbol);

    spheredat.push(Sphere<float>{arad, apos}, acol);

    if(spheredat.is_full()) {
      sphere_buff_atoms_.push(spheredat.length(),
                             spheredat.positions(),
                             spheredat.normals(),
                             spheredat.colors());
      spheredat.resize();
    }
  }

  sphere_buff_atoms_.push(spheredat.length(),
                         spheredat.positions(),
                         spheredat.normals(),
                         spheredat.colors());
}

void
Scene::render_frame()
{
  const auto mv_matrix = model_matrix_ * camera_.view_matrix;
  const auto norm_matrix = Mat3f{Mat4f{mv_matrix}.inverse().transpose()};
  const auto proj_matrix = camera_.projection_matrix();

  glViewport(0, 0, camera_.width, camera_.height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  color_light_shader_.use_program();

  color_light_shader_.projection_matrix(proj_matrix);
  color_light_shader_.modelview_matrix(mv_matrix);
  color_light_shader_.normal_matrix(norm_matrix);

  sphere_buff_atoms_.render(GL_TRIANGLE_STRIP);
  glFlush();
}

void
Scene::rotate(float x, float y, float z)
{
  model_matrix_.rotate(1.0f, 0.0f, 0.0f, x);
  model_matrix_.rotate(0.0f, 1.0f, 0.0f, y);
  model_matrix_.rotate(0.0f, 0.0f, 1.0f, z);
}

void
Scene::calculate_matrices()
{
  // calculate bounding sphere
  Bounding_sphere<float> bs;

  for(auto& model : Molecule::Models_iterable{*molecule_}) {
    for(auto& chain : Model::Chains_iterable{model}) {
      for(auto& residue : Chain::Compound_iterator{chain}) {
        for(auto& atom : Compound::Atoms_iterable{residue}) {
          bs.expand(atom.position());
        }
      }
    }
  }

  const auto fov = camera_.fov;
  const auto theta = fov / 2.0f;
  const auto tan_theta = tan(theta);
  const auto y = bs.radius() + 2.0f;
  const auto focal_len = y / tan_theta;
  const auto near = focal_len - y;
  const auto far = focal_len + y;

  camera_.fov = fov;
  camera_.near = near;
  camera_.far = far;

  camera_.view_matrix.set_translate(0, 0, -focal_len);

  model_matrix_.identity().translate(-bs.center());
}

void
Scene::open_stream(std::istream& is)
{
  sphere_buff_atoms_.reserve(0);
  molecule_ = std::make_unique<Molecule>();
  Pdb_parser parser;
  parser.parse(molecule_.get(), is);
}

typename Scene::Camera_type&
Scene::get_camera()
{
  return camera_;
}

} // namespace molphene
