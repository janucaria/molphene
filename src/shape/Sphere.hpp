#ifndef MOLPHENE_SHAPE_SPHERE_HPP
#define MOLPHENE_SHAPE_SPHERE_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TRadii, typename TCenter = Vec3<TRadii>>
struct Sphere {
  using Radius_type = TRadii;
  using Center_type = TCenter;

  Radius_type radius{0};
  Center_type center{0, 0, 0};

  Sphere() noexcept = default;

  explicit Sphere(Radius_type radii) noexcept
  : radius{radii}
  {
  }

  Sphere(Radius_type radii, Center_type center) noexcept
  : radius{radii}
  , center{center}
  {
  }
};

} // namespace molphene

#endif