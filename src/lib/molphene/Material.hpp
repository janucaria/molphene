#ifndef MOLPHENE_MATERIAL_HPP
#define MOLPHENE_MATERIAL_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class Material {
public:
  using float_t = typename type_configs<TConfig>::float_type;
  using Color = TColor;

  float_t ambient_intensity{0.2};
  Color diffuse_color{0xCC, 0xCC, 0xCC};
  Color emissive_color{0};
  Color specular_color{0};
  float_t shininess{0.2};

  Material() noexcept = default;
};
} // namespace molphene

#endif
