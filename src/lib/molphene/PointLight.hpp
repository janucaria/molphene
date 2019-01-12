#ifndef MOLPHENE_POINT_LIGHT_HPP
#define MOLPHENE_POINT_LIGHT_HPP

#include "BasicLight.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class PointLight : public BasicLight<TColor, TConfig> {
public:
  using typename BasicLight<TColor, TConfig>::float_type;
  using typename BasicLight<TColor, TConfig>::Color;
  using Vec3f = Vec3<float_type>;

  float_type radius{100};

  Vec3f attenuation{1, 0, 0};

  Vec3f location{0, 0, 0};

  using BasicLight<TColor, TConfig>::BasicLight;

  PointLight() noexcept = default;
};
} // namespace molphene

#endif
