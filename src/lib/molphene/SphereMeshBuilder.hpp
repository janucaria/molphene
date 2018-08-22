#ifndef MOLPHENE_SPHERE_MESH_BUILDER_HPP
#define MOLPHENE_SPHERE_MESH_BUILDER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"
#include "shape/UvSphere.hpp"

namespace molphene {

class SphereMeshBuilder {
public:
  using Div = size_t;

public:
  SphereMeshBuilder(size_t max_bytes, Div lat_div, Div long_div);

  void
  build(size_t idx);

  size_t
  get_vertices_size();

  size_t
  size_bytes();

  size_t
  size();

  const std::vector<Vec3f>&
  positions() const noexcept;

  const std::vector<Vec3f>&
  normals() const noexcept;

  const std::vector<Vec2f>&
  texcoords() const noexcept;

  template<typename... Ts>
  Vec2f
  texcoord(Ts&&... args) noexcept
  {
    return tex_ = Vec2f{std::forward<Ts>(args)...};
  }

  UvSphere<float>
  sphere(UvSphere<float> sphere);

private:
  Div lat_div_;

  Div long_div_;

  std::vector<Vec3f> normals_;

  std::vector<Vec3f> positions_;

  std::vector<Vec2f> texcoords_;

  size_t size_;

  Vec2f tex_{0};

  UvSphere<float> sphere_;
};
} // namespace molphene

#endif
