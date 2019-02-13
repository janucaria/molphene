#ifndef MOLPHENE_SHAPE_CYLINDER_HPP
#define MOLPHENE_SHAPE_CYLINDER_HPP

#include "../stdafx.hpp"

#include "../m3d.hpp"

namespace molphene {

template<typename FloatingPoint>
class cylinder {
public:
  using float_type = FloatingPoint;
  using vec3_type = vec3<float_type>;

  float_type radius;
  vec3_type top;
  vec3_type bottom;

  cylinder() noexcept = default;

  auto height() const noexcept -> std::size_t
  {
    return (top - bottom).magnitude();
  }
};

} // namespace molphene

#endif