#ifndef MOLPHENE_BASIC_LIGHT_HPP
#define MOLPHENE_BASIC_LIGHT_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class BasicLight {
public:
  using float_t = typename type_configs<TConfig>::float_type;
  using Color = TColor;

  float_t ambient_intensity{0};

  Color color{0xFFFFFF};

  float_t intensity{1};

  BasicLight() noexcept = default;
};
} // namespace molphene

#endif
