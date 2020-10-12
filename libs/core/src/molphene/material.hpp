#ifndef MOLPHENE_MATERIAL_HPP
#define MOLPHENE_MATERIAL_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class Material {
public:
  using float_type = typename type_configs<TConfig>::float_type;
  using color_type = TColor;

  float_type ambient_intensity{0.2};
  color_type diffuse_color{0xCC, 0xCC, 0xCC};
  color_type emissive_color{0};
  color_type specular_color{0};
  float_type shininess{0.2};

  constexpr Material() noexcept = default;
};
} // namespace molphene

#endif
