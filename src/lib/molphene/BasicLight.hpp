#ifndef MOLPHENE_BASIC_LIGHT_HPP
#define MOLPHENE_BASIC_LIGHT_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
class BasicLight {
public:
  using Color = TColor;
  using Vec3 = TVector;

  float ambient_intensity{0};

  Color color{0xFFFFFF};

  float intensity{1};

  BasicLight() noexcept = default;
};
} // namespace molphene

#endif
