#ifndef MOLPHENE_BOUNDING_SPHERE_HPP
#define MOLPHENE_BOUNDING_SPHERE_HPP

#include "m3d.hpp"
#include "shape/sphere.hpp"

namespace molphene {

template<typename TRadii>
class bounding_sphere {
public:
  using sphere = sphere<TRadii>;
  using sphere_radius = typename sphere::float_type;
  using sphere_center = typename sphere::vec3_type;
  using center_type = sphere_center;

private:
  sphere sphere_{-1};

public:
  bounding_sphere() noexcept = default;

  void expand(sphere_center position) noexcept
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

  auto center() const noexcept -> sphere_center
  {
    return sphere_.center;
  }

  auto radius() const noexcept -> sphere_radius
  {
    return sphere_.radius;
  }

  void reset() noexcept
  {
    sphere_.radius = -1;
  }
};
} // namespace molphene

#endif