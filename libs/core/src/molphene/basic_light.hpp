#ifndef MOLPHENE_BASIC_LIGHT_HPP
#define MOLPHENE_BASIC_LIGHT_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class basic_light {
public:
  using float_type = typename type_configs<TConfig>::float_type;
  using color_type = TColor;

  float_type ambient_intensity{0};

  color_type color{0xFF, 0xFF, 0xFF};

  float_type intensity{1};

  constexpr basic_light() noexcept = default;
};
} // namespace molphene

#endif
