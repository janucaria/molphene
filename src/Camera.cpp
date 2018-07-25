#include "Camera.h"
#include <boost/algorithm/clamp.hpp>
#include <cfloat>
#include <cmath>

namespace molphene {
Camera::Camera()
: far(0.0f)
, near(0.0f)
, fov(0.0f)
, aspect(0.0f)
{
}

void
Camera::setAspect(const float& val)
{
  aspect = val;
}

void
Camera::setNear(const float& val)
{
  near = val;
}

void
Camera::setFar(const float& val)
{
  far = val;
}

void
Camera::setFov(const float& val)
{
  fov = val;
}

void
Camera::updateProjectionMatrix()
{
  float top = tan(fov / 2.0f) * near;
  float bottom = -top;

  float left = aspect * bottom;
  float right = aspect * top;

  projectionMatrix.frustum(left, right, bottom, top, near, far);
}

void
Camera::translate(const float& x, const float& y, const float& z)
{
  viewMatrix.identity();
  viewMatrix.translate(-x, -y, -z);
}

void
Camera::zoom(float z)
{
  fov = boost::algorithm::clamp(fov * z, FLT_EPSILON, M_PI - FLT_EPSILON);
}

const mat4f&
Camera::getProjectionMatrix() const
{
  return projectionMatrix;
}

const mat4f&
Camera::getViewMatrix() const
{
  return viewMatrix;
}

} // namespace molphene