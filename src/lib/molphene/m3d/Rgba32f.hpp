#ifndef MOLPHENE_M3D_RGBA32F_HPP
#define MOLPHENE_M3D_RGBA32F_HPP

#include "Rgba8.hpp"

namespace molphene {

struct Rgba32f {
  float r, g, b, a;

  Rgba32f() noexcept = default;

  Rgba32f(float c, float a) noexcept;

  Rgba32f(float r, float g, float b, float a = 1.0) noexcept;
  
  explicit Rgba32f(float c) noexcept;

  explicit Rgba32f(const Rgba8& c8) noexcept;

  Rgba32f&
  operator+=(const Rgba32f& rsh);

  Rgba32f&
  operator-=(const Rgba32f& rsh);

  Rgba32f&
  operator()(float r, float g, float b, float a = 1.0);
};

Rgba32f
operator+(const Rgba32f& lsh, const Rgba32f& rsh);

Rgba32f
operator-(const Rgba32f& lsh, const Rgba32f& rsh);
} // namespace molphene

#endif
