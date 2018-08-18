#ifndef MOLPHENE_SPOT_LIGHT_HPP
#define MOLPHENE_SPOT_LIGHT_HPP

#include "stdafx.hpp"

#include "Directional_light.hpp"
#include "Point_light.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
struct Spot_light : Point_light<TColor, TVector> {
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
