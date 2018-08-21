#ifndef MOLPHENE_MATERIAL_HPP
#define MOLPHENE_MATERIAL_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TScalar = float>
class Material {
public:
  using Color = TColor;
  using Scalar = TScalar;

  Scalar ambient_intensity{0.2};
  Color diffuse_color{0xCCCCCC};
  Color emissive_color{0};
  Color specular_color{0};
  Scalar shininess{0.2};

  Material() noexcept = default;
};
} // namespace molphene

#endif
