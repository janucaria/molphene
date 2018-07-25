#ifndef __molphene__Scene__
#define __molphene__Scene__

#include "BoundingSphere.h"
#include "Camera.h"
#include "ColorLightRenderer.h"
#include "ColourManager.h"
#include "PDBParser.h"
#include "Renderer.h"
#include "atom.h"
#include "bond.h"
#include "color_light_buffer.h"
#include "m3d.hpp"
#include "model.h"
#include "molecule.h"
#include "opengl.h"
#include "sphere_buffer.h"
#include <fstream>
#include <istream>

namespace molphene {
typedef unsigned char colormode_t;

class Scene {
public:
  Scene();

  virtual ~Scene();

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

  molecule* molecule_;

  ColourManager colorManager;
};

} // namespace molphene

#endif
