#ifndef MOLPHENE_SHAPE_UV_SPHERE_HPP
#define MOLPHENE_SHAPE_UV_SPHERE_HPP

#include "Sphere.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TRadii, typename TCenter = Vec3<TRadii>>
struct UvSphere : public Sphere<TRadii, TCenter> {
  using typename Sphere<TRadii, TCenter>::Radius_type;
  using typename Sphere<TRadii, TCenter>::Center_type;
  using Axis_type = Center_type;

  Axis_type axis{0, 1, 0};

  using Sphere<TRadii, TCenter>::Sphere;

  UvSphere() noexcept = default;

  UvSphere(Radius_type radii, Center_type center, Axis_type axis) noexcept
  : Sphere<TRadii, TCenter>{radii, center}
  , axis{axis}
  {
  }
};

} // namespace molphene

#endif