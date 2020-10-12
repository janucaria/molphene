#ifndef MOLPHENE_CYLINDER_MESH_ATTRIBUTE_HPP
#define MOLPHENE_CYLINDER_MESH_ATTRIBUTE_HPP

#include "m3d.hpp"
#include "shape/cylinder.hpp"

namespace molphene {

struct cylinder_mesh_attribute {
  rgba8 color{};
  std::size_t index{};
  vec2<double> texcoord{};
  Cylinder<double> cylinder;
};

} // namespace molphene

#endif
