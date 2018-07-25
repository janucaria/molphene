#ifndef MOLPHENE_BOUNDING_SPHERE_HPP
#define MOLPHENE_BOUNDING_SPHERE_HPP

#include "m3d.hpp"
#include "shape/Sphere.hpp"

namespace molphene {

template<typename TRadii, typename TCenter = Vec3<TRadii>>
class Bounding_sphere {
public:
  using Sphere_type = Sphere<TRadii, TCenter>;
  using Sphere_Radius_type = typename Sphere_type::Radius_type;
  using Sphere_Center_type = typename Sphere_type::Center_type;

private:
  Sphere_type sphere_{-1};

public:
  Bounding_sphere() noexcept = default;

  void
  expand(Sphere_Center_type position) noexcept
  {
    if(sphere_.radius < 0.0) {
      sphere_.center = position;
      sphere_.radius = 0.0f;
      return;
    }

    const auto p_sub_q = position - sphere_.center;
    const auto mag_p_sub_q = p_sub_q.magnitude();

    if(mag_p_sub_q * mag_p_sub_q > sphere_.radius * sphere_.radius) {
      const auto g = sphere_.center - p_sub_q * sphere_.radius / mag_p_sub_q;

      sphere_.center = (g + position) / 2;
      sphere_.radius = (g - sphere_.center).magnitude();
    }
  }

  Sphere_Center_type
  center() const noexcept
  {
    return sphere_.center;
  }

  Sphere_Radius_type
  radius() const noexcept
  {
    return sphere_.radius;
  }

  void
  reset() noexcept
  {
    sphere_.radius = -1;
  }
};
} // namespace molphene

#endif
