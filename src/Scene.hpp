#ifndef __molphene__Scene__
#define __molphene__Scene__

#include <fstream>
#include <istream>
#include <memory>

#include "Bounding_sphere.hpp"
#include "Camera.hpp"
#include "Color_light_shader.hpp"
#include "Colour_manager.hpp"
#include "mol/Pdb_parser.hpp"
#include "mol/Atom.hpp"
#include "mol/Bond.hpp"
#include "Color_light_buffer.hpp"
#include "m3d.hpp"
#include "mol/Model.hpp"
#include "mol/Molecule.hpp"
#include "opengl.hpp"
#include "Material.hpp"
#include "Directional_light.hpp"

namespace molphene {
typedef unsigned char colormode_t;

class Scene {
public:

  using Camera_type = Camera<float, unsigned int>;

  bool
  setupGraphics();

  void
  resetMesh();

  void
  changeDimension(GLsizei width, GLsizei height);

  void
  clearRect();

  void
  renderFrame();

  void
  rotate(float x, float y, float z);

  void
  openStream(std::istream& is);

  void
  reset_molecules();

  Camera_type&
  get_camera();

private:
  Color_light_buffer sphere_buff_atoms;

  Color_light_shader color_light_shader_;

  Directional_light<Rgba8, Vec3f> light_source_;

  Material<Rgba8, unsigned int> material_;

  mat4f modelMatrix;

  Camera_type camera_;

  std::unique_ptr<Molecule> molecule_;

  Colour_manager colour_manager;
};

} // namespace molphene

#endif
