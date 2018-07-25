#include "BoundingSphere.h"

namespace molphene {

BoundingSphere::BoundingSphere() = default;

void
BoundingSphere::expand(const vec3f& position)
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

void
BoundingSphere::reset()
{
    sphere_.radius = -1;
}

vec3f
BoundingSphere::getCenter()
{
  return sphere_.center;
}

float
BoundingSphere::getRadius()
{
  return sphere_.radius;
}

} // namespace molphene