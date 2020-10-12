#ifndef MOLPHENE_POINT_LIGHT_HPP
#define MOLPHENE_POINT_LIGHT_HPP

#include "basic_light.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class PointLight : public basic_light<TColor, TConfig> {
public:
  using typename basic_light<TColor, TConfig>::float_type;
  using typename basic_light<TColor, TConfig>::color_type;
  using vec3f = vec3<float_type>;

  float_type radius{100};

  vec3f attenuation{1, 0, 0};

  vec3f location{0, 0, 0};

  using basic_light<TColor, TConfig>::basic_light;

  constexpr PointLight() noexcept = default;
};
} // namespace molphene

#endif
