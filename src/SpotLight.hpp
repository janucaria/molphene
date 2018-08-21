#ifndef MOLPHENE_SPOT_LIGHT_HPP
#define MOLPHENE_SPOT_LIGHT_HPP

#include "stdafx.hpp"

#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
struct SpotLight : PointLight<TColor, TVector> {
  using typename PointLight<TColor, TVector>::Color;
  using typename PointLight<TColor, TVector>::Vec3;

  float beam_width{M_PI / 4};

  float cut_off_angle{M_PI / 2};

  Vec3 direction{0, 0, -1};
  
  using PointLight<TColor, TVector>::PointLight;

  SpotLight() noexcept = default;
};
} // namespace molphene

#endif
