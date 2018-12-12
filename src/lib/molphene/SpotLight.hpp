#ifndef MOLPHENE_SPOT_LIGHT_HPP
#define MOLPHENE_SPOT_LIGHT_HPP

#include "stdafx.hpp"

#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class SpotLight : public PointLight<TColor, TConfig> {
public:
  using typename PointLight<TColor, TConfig>::float_t;
  using typename PointLight<TColor, TConfig>::Color;
  using Vec3f = Vec3<float_t>;

  float_t beam_width{M_PI / 4};

  float_t cut_off_angle{M_PI / 2};

  Vec3f direction{0, 0, -1};

  using PointLight<TColor, TConfig>::PointLight;

  SpotLight() noexcept = default;
};
} // namespace molphene

#endif
