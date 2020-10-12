#ifndef MOLPHENE_SHAPE_CYLINDER_HPP
#define MOLPHENE_SHAPE_CYLINDER_HPP

#include "../stdafx.hpp"

#include "../m3d.hpp"

namespace molphene {

template<typename FloatingPoint>
class Cylinder {
public:
  using float_type = FloatingPoint;
  using vec3_type = vec3<float_type>;

  float_type radius{1};
  vec3_type top{0, 1, 0};
  vec3_type bottom{0, -1, 0};

  constexpr Cylinder() noexcept = default;

  constexpr auto height() const noexcept -> std::size_t
  {
    return (top - bottom).magnitude();
  }
};

} // namespace molphene

#endif
