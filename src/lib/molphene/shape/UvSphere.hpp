#ifndef MOLPHENE_SHAPE_UV_SPHERE_HPP
#define MOLPHENE_SHAPE_UV_SPHERE_HPP

#include "../m3d.hpp"
#include "Sphere.hpp"

namespace molphene {

template<typename TRadii, typename TCenter = Vec3<TRadii>>
struct UvSphere : public Sphere<TRadii, TCenter> {
  using typename Sphere<TRadii, TCenter>::Radius;
  using typename Sphere<TRadii, TCenter>::Center;
  using Axis = Center;

  Axis axis{0, 1, 0};

  using Sphere<TRadii, TCenter>::Sphere;

  UvSphere() noexcept = default;

  UvSphere(Radius radii, Center center, Axis axis) noexcept
  : Sphere<TRadii, TCenter>{radii, center}
  , axis{axis}
  {
  }
};

} // namespace molphene

#endif