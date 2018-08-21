#ifndef MOLPHENE_BASIC_LIGHT_HPP
#define MOLPHENE_BASIC_LIGHT_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
struct BasicLight {
  using Color_type = TColor;
  using Vec3_type = TVector;

  float ambient_intensity{0};

  Color_type color{0xFFFFFF};

  float intensity{1};

  BasicLight() noexcept = default;
};
} // namespace molphene

#endif
