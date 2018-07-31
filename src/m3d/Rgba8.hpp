#ifndef MOLPHENE_M3D_RGBA8_HPP
#define MOLPHENE_M3D_RGBA8_HPP

#include <cstdint>

namespace molphene {

struct Rgba8 {
  uint8_t r{0};
  uint8_t g{0};
  uint8_t b{0};
  uint8_t a{255};

  Rgba8() noexcept = default;

  Rgba8(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept;

  explicit Rgba8(uint32_t i) noexcept;

  Rgba8&
  operator+=(const Rgba8& rsh);

  Rgba8&
  operator-=(const Rgba8& rsh);

  Rgba8&
  operator()(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

  Rgba8&
  operator()(uint32_t i);

  Rgba8&
  operator=(uint32_t i);
};

Rgba8
operator+(const Rgba8& lsh, const Rgba8& rsh);

Rgba8
operator-(const Rgba8& lsh, const Rgba8& rsh);

} // namespace molphene

#endif
