#ifndef MOLPHENE_BOUNDING_SPHERE_HPP
#define MOLPHENE_BOUNDING_SPHERE_HPP

#include "m3d.hpp"
#include "shape/Sphere.hpp"

namespace molphene {

template<typename TRadii>
class BoundingSphere {
public:
  using Sphere = Sphere<TRadii>;
  using SphereRadius = typename Sphere::Radius;
  using SphereCenter = typename Sphere::Center;
  using center_type = SphereCenter;

private:
  Sphere sphere_ {-1};

public:
  BoundingSphere() noexcept = default;

  void
  expand(SphereCenter position) noexcept
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

  SphereCenter
  center() const noexcept
  {
    return sphere_.center;
  }

  SphereRadius
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
