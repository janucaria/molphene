#ifndef MOLPHENE_CYLINDER_MESH_ATTRIBUTE_HPP
#define MOLPHENE_CYLINDER_MESH_ATTRIBUTE_HPP

namespace molphene {

struct cylinder_mesh_attribute {
  rgba8 color;
  std::size_t index;
  vec2<double> texcoord;
  cylinder<double> cylinder;
};

} // namespace molphene

#endif
