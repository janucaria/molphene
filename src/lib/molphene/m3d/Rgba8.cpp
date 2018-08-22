#include "Rgba8.hpp"

namespace molphene {

Rgba8::Rgba8(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept
: r{r}
, g{g}
, b{b}
, a{a}
{
}

Rgba8::Rgba8(uint32_t i) noexcept
: Rgba8((i & 0x00FF0000u) >> 16u,
        (i & 0x0000FF00u) >> 8u,
        i & 0x000000FFu,
        (i >> 24u) ^ 0xFFu)
{
}

Rgba8&
Rgba8::operator+=(const Rgba8& rsh)
{
  r = (255 - r) > rsh.r ? r + rsh.r : 255;
  g = (255 - g) > rsh.g ? g + rsh.g : 255;
  b = (255 - b) > rsh.b ? b + rsh.b : 255;
  a = (255 - a) > rsh.a ? a + rsh.a : 255;

  return *this;
}

Rgba8&
Rgba8::operator-=(const Rgba8& rsh)
{
  r = rsh.r < r ? r - rsh.r : 0;
  g = rsh.g < g ? g - rsh.g : 0;
  b = rsh.b < b ? b - rsh.b : 0;
  a = rsh.a < a ? a - rsh.a : 0;

  return *this;
}

Rgba8&
Rgba8::operator()(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;

  return *this;
}

Rgba8&
Rgba8::operator()(uint32_t i)
{
  return this->operator()((i & 0x00FF0000u) >> 16u,
                          (i & 0x0000FF00u) >> 8u,
                          i & 0x000000FFu,
                          (i >> 24u) ^ 0xFFu);
}

Rgba8&
Rgba8::operator=(uint32_t i)
{
  this->operator()((i & 0x00FF0000u) >> 16u,
                   (i & 0x0000FF00u) >> 8u,
                   i & 0x000000FFu,
                   (i >> 24u) ^ 0xFFu);

  return *this;
}

Rgba8
operator+(const Rgba8& lsh, const Rgba8& rsh)
{
  return Rgba8(lsh).operator+=(rsh);
}

Rgba8
operator-(const Rgba8& lsh, const Rgba8& rsh)
{
  return Rgba8(lsh).operator-=(rsh);
}

} // namespace molphene
