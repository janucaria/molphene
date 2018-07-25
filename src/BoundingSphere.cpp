#include "BoundingSphere.h"

namespace molphene {

BoundingSphere::BoundingSphere()
{
  radius = -1.0f;
}

void
BoundingSphere::expand(const vec3f& position)
{
  if(radius < 0.0) {
    center = position;
    radius = 0.0f;
  } else {
    vec3f pSubQ = position - center;
    float magPSubQ = pSubQ.magnitude();

    if(magPSubQ * magPSubQ > radius * radius) {
      vec3f G = center - pSubQ * radius / magPSubQ;

      center = (G + position) / 2;
      radius = (G - center).magnitude();
    }
  }
}

void
BoundingSphere::reset()
{
  radius = -1.0f;
}

vec3f
BoundingSphere::getCenter()
{
  return center;
}

float
BoundingSphere::getRadius()
{
  return radius;
}

} // namespace molphene