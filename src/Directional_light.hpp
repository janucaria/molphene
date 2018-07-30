#ifndef MOLPHENE_DIRECTIONAL_LIGHT_HPP
#define MOLPHENE_DIRECTIONAL_LIGHT_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
class Directional_light {
public:
  using Color_type = TColor;
  using Vec3_type = TVector;

  using Ambient_type = Color_type;
  using Diffuse_type = Color_type;
  using Specular_tye = Color_type;
  using Direction_type = Vec3_type;

  Ambient_type ambient;

  Diffuse_type diffuse;

  Specular_tye specular;

  Direction_type direction{0, 1, 0};

  Directional_light() = default;
};
} // namespace molphene

#endif
