#ifndef MOLPHENE_SPHERE_MESH_ATTRIBUTE_HPP
#define MOLPHENE_SPHERE_MESH_ATTRIBUTE_HPP

#include "m3d.hpp"

namespace molphene {

struct sphere_mesh_attribute {
  rgba8 color;
  std::size_t index;
  vec2<double> texcoord;
  sphere<double> sphere;
};

} // namespace molphene
#endif