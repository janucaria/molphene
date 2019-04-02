#ifndef MOLPHENE_FOG_HPP
#define MOLPHENE_FOG_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class fog {
public:
  using color_type = TColor;
  using float_type = typename type_configs<TConfig>::float_type;

  enum class type { linear, exponential };

  float_type visibility_range{0};

  color_type color{0xFF, 0xFF, 0xFF};

  type fog_type{type::linear};

  constexpr fog() noexcept = default;
};
} // namespace molphene

#endif
