#ifndef MOLPHENE_DIRECTIONAL_LIGHT_HPP
#define MOLPHENE_DIRECTIONAL_LIGHT_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
class Directional_light {
public:
  using Color_type = TColor;
  using Vec3_type = TVector;

  float ambient_intensity{0};
  
  Color_type color{0xFFFFFF};
  
  Vec3_type direction{0, 0, -1};

  float intensity{1};

  Directional_light() noexcept = default;
};
} // namespace molphene

#endif
