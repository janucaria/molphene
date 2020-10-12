#ifndef MOLPHENE_SPOT_LIGHT_HPP
#define MOLPHENE_SPOT_LIGHT_HPP

#include "stdafx.hpp"

#include "directional_light.hpp"
#include "m3d.hpp"
#include "point_light.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class SpotLight : public PointLight<TColor, TConfig> {
public:
  using typename PointLight<TColor, TConfig>::float_type;
  using typename PointLight<TColor, TConfig>::color_type;
  using vec3f = vec3<float_type>;

  float_type beam_width{M_PI / 4};

  float_type cut_off_angle{M_PI / 2};

  vec3f direction{0, 0, -1};

  using PointLight<TColor, TConfig>::PointLight;

  constexpr SpotLight() noexcept = default;
};
} // namespace molphene

#endif
