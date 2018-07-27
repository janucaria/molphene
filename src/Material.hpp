#ifndef MOLPHENE_MATERIAL_HPP
#define MOLPHENE_MATERIAL_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TShininess>
class Material {
public:
  using Color_type = TColor;

  using Ambient_type = Color_type;
  using Diffuse_type = Color_type;
  using Specular_type = Color_type;
  using Shininess_type = TShininess;

  Ambient_type ambient;

  Diffuse_type diffuse;

  Specular_type specular;

  Shininess_type shininess{0};

  Material() noexcept = default;

  Material(Ambient_type ambient,
           Diffuse_type diffuse,
           Specular_type specular,
           Shininess_type shininess) noexcept
  : ambient{ambient}
  , diffuse{diffuse}
  , specular{specular}
  , shininess{shininess}
  {
  }
};
} // namespace molphene

#endif
