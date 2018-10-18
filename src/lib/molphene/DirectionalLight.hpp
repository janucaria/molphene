#ifndef MOLPHENE_DIRECTIONAL_LIGHT_HPP
#define MOLPHENE_DIRECTIONAL_LIGHT_HPP

#include "BasicLight.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class DirectionalLight : public BasicLight<TColor, TConfig> {
public:
  using typename BasicLight<TColor, TConfig>::float_t;
  using typename BasicLight<TColor, TConfig>::Color;
  using Vec3f = Vec3<float_t>;

  Vec3f direction {0, 0, -1};

  using BasicLight<TColor, TConfig>::BasicLight;

  DirectionalLight() noexcept = default;
};
} // namespace molphene

#endif
