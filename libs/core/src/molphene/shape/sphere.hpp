#ifndef MOLPHENE_SHAPE_SPHERE_HPP
#define MOLPHENE_SHAPE_SPHERE_HPP

#include "../m3d.hpp"

namespace molphene {

template<typename FloatP>
class Sphere {
public:
  using float_type = FloatP;
  using vec3_type = vec3<float_type>;

  float_type radius{1};
  vec3_type center{0, 0, 0};

  constexpr Sphere() noexcept = default;

  explicit constexpr Sphere(float_type radii) noexcept
  : radius{radii}
  {
  }

  constexpr Sphere(float_type radii, vec3_type center) noexcept
  : radius{radii}
  , center{center}
  {
  }

  template<typename U,
           typename = std::enable_if_t<std::is_constructible_v<vec3_type, U>>>
  explicit constexpr Sphere(const Sphere<U>& sphere) noexcept
  : radius(sphere.radius)
  , center(sphere.center)
  {
  }

  template<typename U,
           typename = std::enable_if_t<std::is_constructible_v<vec3_type, U>>>
  constexpr Sphere(U radii, vec3<U> center) noexcept
  : radius(radii)
  , center(center)
  {
  }
};

} // namespace molphene

#endif