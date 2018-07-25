#ifndef __Molphene__BoundingSphere__
#define __Molphene__BoundingSphere__

#include "m3d.hpp"
#include "shape/Sphere.hpp"

namespace molphene {
class BoundingSphere {
public:
  using Sphere_type = Sphere<float>;
  using Sphere_Radius_type = typename Sphere_type::Radius_type;
  using Sphere_Center_type = typename Sphere_type::Center_type;

private:
  Sphere_type sphere_{-1};

public:
  BoundingSphere();
  void
  reset();
  void
  expand(const vec3f& position);
  float
  getRadius();
  vec3f
  getCenter();
};

} // namespace molphene

#endif
