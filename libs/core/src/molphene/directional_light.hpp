#ifndef MOLPHENE_DIRECTIONAL_LIGHT_HPP
#define MOLPHENE_DIRECTIONAL_LIGHT_HPP

#include "basic_light.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class DirectionalLight : public basic_light<TColor, TConfig> {
public:
  using typename basic_light<TColor, TConfig>::float_type;
  using typename basic_light<TColor, TConfig>::color_type;
  using vec3f = vec3<float_type>;

  vec3f direction{0, 0, -1};

  using basic_light<TColor, TConfig>::basic_light;

  constexpr DirectionalLight() noexcept = default;
};
} // namespace molphene

#endif
