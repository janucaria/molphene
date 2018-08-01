#ifndef MOLPHENE_SPOT_LIGHT_HPP
#define MOLPHENE_SPOT_LIGHT_HPP

#include <cmath>

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
class Spot_light {
public:
  using Color_type = TColor;
  using Vec3_type = TVector;

  float ambient_intensity{0};

  float beam_width{M_PI / 4};

  float cut_off_angle{M_PI / 2};

  float intensity{1};

  float radius{100};

  Color_type color{0xFFFFFF};

  Vec3_type attenuation{1, 0, 0};

  Vec3_type direction{0, 0, -1};

  Vec3_type location{0, 0, 0};

  Spot_light() noexcept = default;
};
} // namespace molphene

#endif
