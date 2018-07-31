#ifndef MOLPHENE_MATERIAL_HPP
#define MOLPHENE_MATERIAL_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TScalar = float>
class Material {
public:
  using Color_type = TColor;
  using Scalar_type = TScalar;

  Scalar_type ambient_intensity{0.2};
  Color_type diffuse_color{0xCCCCCC};
  Color_type emissive_color;
  Color_type specular_color;
  Scalar_type shininess{0.2};

  Material() noexcept = default;
};
} // namespace molphene

#endif
