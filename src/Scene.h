#ifndef __molphene__Scene__
#define __molphene__Scene__

#include "Bounding_sphere.hpp"
#include "Camera.h"
#include "ColorLightRenderer.h"
#include "ColourManager.h"
#include "mol/Pdb_parser.hpp"
#include "Renderer.h"
#include "mol/Atom.hpp"
#include "mol/Bond.hpp"
#include "color_light_buffer.h"
#include "m3d.hpp"
#include "mol/Model.hpp"
#include "mol/Molecule.hpp"
#include "opengl.h"
#include "sphere_buffer.h"
#include <fstream>
#include <istream>
#include <memory>

namespace molphene {
typedef unsigned char colormode_t;

class Scene {
public:

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

  void
  zoom(float z);

private:
  sphere_buffer sphere_buff_atoms;

  Renderer renderer;

  mat4f modelMatrix;

  Camera camera;

  std::unique_ptr<Molecule> molecule_;

  ColourManager colorManager;
};

} // namespace molphene

#endif
