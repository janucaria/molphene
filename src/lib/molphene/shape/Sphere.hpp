#ifndef MOLPHENE_SHAPE_SPHERE_HPP
#define MOLPHENE_SHAPE_SPHERE_HPP

#include "../m3d.hpp"

namespace molphene {

template<typename TRadii>
class Sphere {
public:
  using Radius = TRadii;
  using Center = Vec3<TRadii>;

  Radius radius {0};
  Center center {0, 0, 0};

  Sphere() noexcept = default;

  explicit Sphere(Radius radii) noexcept
  : radius {radii}
  {
  }

  Sphere(Radius radii, Center center) noexcept
  : radius {radii}
  , center {center}
  {
  }

  template<typename U,
           typename = std::enable_if_t<std::is_constructible_v<Center, U>>>
  explicit Sphere(const Sphere<U>& sphere) noexcept
  : radius(sphere.radius)
  , center(sphere.center)
  {
  }

  template<typename U,
           typename = std::enable_if_t<std::is_constructible_v<Center, U>>>
  Sphere(U radii, Vec3<U> center) noexcept
  : radius(radii)
  , center(center)
  {
  }
};

} // namespace molphene

#endif