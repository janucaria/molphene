#ifndef MOLPHENE_SHAPE_UV_SPHERE_HPP
#define MOLPHENE_SHAPE_UV_SPHERE_HPP

#include "../m3d.hpp"
#include "Sphere.hpp"

namespace molphene {

template<typename TRadii>
class UvSphere : public Sphere<TRadii> {
public:
  using typename Sphere<TRadii>::Radius;
  using typename Sphere<TRadii>::Center;
  using Axis = Center;

  Axis axis{0, 1, 0};

  using Sphere<TRadii>::Sphere;

  UvSphere() noexcept = default;

  UvSphere(Radius radii, Center center, Axis axis) noexcept
  : Sphere<TRadii>{radii, center}
  , axis{axis}
  {
  }

  template<typename U,
           typename = std::enable_if_t<std::is_constructible_v<Center, U>>>
  explicit UvSphere(const UvSphere<U>& sphere) noexcept
  : Sphere<TRadii>(sphere.radius, sphere.center)
  , axis(sphere.axis)
  {
  }
};

} // namespace molphene

#endif