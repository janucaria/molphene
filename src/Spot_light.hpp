#ifndef MOLPHENE_SPOT_LIGHT_HPP
#define MOLPHENE_SPOT_LIGHT_HPP

#include <cmath>

#include "m3d.hpp"
#include "Point_light.hpp"

namespace molphene {

template<typename TColor, typename TVector>
class Spot_light : public Point_light<TColor, TVector> {
public:
  using typename Point_light<TColor, TVector>::Color_type;
  using typename Point_light<TColor, TVector>::Vec3_type;

  float beam_width{M_PI / 4};

  float cut_off_angle{M_PI / 2};

  Vec3_type direction{0, 0, -1};

  using Point_light<TColor, TVector>::Point_light;

  Spot_light() noexcept = default;
};
} // namespace molphene

#endif
