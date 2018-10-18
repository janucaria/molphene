#include "Rgba32f.hpp"

namespace molphene {

Rgba32f::Rgba32f(float c) noexcept
: Rgba32f {c, c}
{
}

Rgba32f::Rgba32f(float c, float a) noexcept
: Rgba32f {c, c, c, a}
{
}

Rgba32f::Rgba32f(float r, float g, float b, float a) noexcept
: r {r}
, g {g}
, b {b}
, a {a}
{
}

Rgba32f::Rgba32f(const Rgba8& c8) noexcept
: r {float(c8.r) / 255}
, g {float(c8.g) / 255}
, b {float(c8.b) / 255}
, a {float(c8.a) / 255}
{
}

Rgba32f&
Rgba32f::operator+=(const Rgba32f& rsh) noexcept
{
  r = (1.0f - r) > rsh.r ? r + rsh.r : 1.0f;
  g = (1.0f - g) > rsh.g ? g + rsh.g : 1.0f;
  b = (1.0f - b) > rsh.b ? b + rsh.b : 1.0f;
  a = (1.0f - a) > rsh.a ? a + rsh.a : 1.0f;

  return *this;
}

Rgba32f&
Rgba32f::operator-=(const Rgba32f& rsh) noexcept
{
  r = rsh.r < r ? r - rsh.r : 0.0f;
  g = rsh.g < g ? g - rsh.g : 0.0f;
  b = rsh.b < b ? b - rsh.b : 0.0f;
  a = rsh.a < a ? a - rsh.a : 0.0f;

  return *this;
}

Rgba32f&
Rgba32f::operator()(float r, float g, float b, float a) noexcept
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;

  return *this;
}

Rgba32f
operator+(const Rgba32f& lsh, const Rgba32f& rsh) noexcept
{
  return Rgba32f(lsh).operator+=(rsh);
}

Rgba32f
operator-(const Rgba32f& lsh, const Rgba32f& rsh) noexcept
{
  return Rgba32f(lsh).operator-=(rsh);
}

} // namespace molphene
