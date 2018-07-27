#include "Scene.h"
#include "m3d.hpp"
#include "shape/Sphere.hpp"
#include "sphere_data.h"

namespace molphene {

bool
Scene::setupGraphics()
{
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glEnable(GL_DEPTH_TEST);
  std::cout << "Hello World" << std::endl;

  renderer.setupGL();

  renderer.useGLProgram();

  light_source_.ambient = 0x7F7F7Fu;
  light_source_.diffuse = 0xFFFFFFu;
  light_source_.specular = 0x7F7F7Fu;
  light_source_.direction = {0.0, 0.0, 0.0};

  material_.ambient = 0x4C4C4Cu;
  material_.diffuse = 0xFFFFFFu;
  material_.specular = 0x7F7F7Fu;
  material_.shininess = 10;

  renderer.light_source(light_source_);
  renderer.material(material_);

  sphere_buff_atoms.setup();

  return true;
}

void
Scene::changeDimension(GLsizei width, GLsizei height)
{
  camera.setAspect(1.0f * width / height);
  camera.updateProjectionMatrix();

  glViewport(0, 0, width, height);
}

void
Scene::resetMesh()
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

  sphere_data spheredat;

  GLuint totalAtoms = static_cast<GLuint>(atoms.size());
  spheredat.reserve(totalAtoms);
  GLuint totalVertices = totalAtoms * spheredat.unitlen();
  sphere_buff_atoms.reserve(totalVertices);

  for(unsigned int i = 0; i < totalAtoms; ++i) {
    auto& atm = *atoms.at(i);
    const auto element = atm.element();
    const auto apos = atm.position();
    const auto arad = element.rvdw;
    const auto acol = colorManager.getElementColor(element.symbol);

    spheredat.push(Sphere<float>{arad, apos}, acol);

    if(spheredat.is_full()) {
      sphere_buff_atoms.push(spheredat.length(),
                             spheredat.positions(),
                             spheredat.normals(),
                             spheredat.colors());
      spheredat.resize();
    }
  }

  sphere_buff_atoms.push(spheredat.length(),
                         spheredat.positions(),
                         spheredat.normals(),
                         spheredat.colors());
}

void
Scene::clearRect()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
Scene::renderFrame()
{
  clearRect();

  mat4f modelViewMatrix = modelMatrix * camera.getViewMatrix();
  mat3f normalMalrix = mat3f(mat4f(modelViewMatrix).inverse().transpose());

  renderer.useGLProgram();
  renderer.projection_matrix(camera.getProjectionMatrix());
  renderer.modelview_matrix(modelViewMatrix);
  renderer.normal_matrix(normalMalrix);

  renderer.render(sphere_buff_atoms);

  glFlush();
}

void
Scene::rotate(float x, float y, float z)
{
  modelMatrix.rotate(1.0f, 0.0f, 0.0f, x);
  modelMatrix.rotate(0.0f, 1.0f, 0.0f, y);
  modelMatrix.rotate(0.0f, 0.0f, 1.0f, z);
  renderFrame();
}

void
Scene::reset_molecules()
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


  float fov = M_PI / 4.0f;
  float theta = fov / 2.0f;
  float tanTheta = tan(theta);
  float y = bs.radius() + 2.0f;
  float focalLength = y / tanTheta;
  float near = focalLength - y;
  float far = focalLength + y;

  camera.setFov(fov);
  camera.setNear(near);
  camera.setFar(far);
  camera.translate(0, 0, focalLength);
  camera.updateProjectionMatrix();

  modelMatrix.identity();
  modelMatrix.translate(-bs.center());
}

void
Scene::openStream(std::istream& is)
{
  sphere_buff_atoms.reserve(0);
  molecule_ = std::make_unique<Molecule>();

  Pdb_parser parser;
  parser.parse(molecule_.get(), is);

  reset_molecules();
}

void
Scene::zoom(float z)
{
  camera.zoom(z);
  camera.updateProjectionMatrix();
}

} // namespace molphene
