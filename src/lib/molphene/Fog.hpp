#ifndef MOLPHENE_FOG_HPP
#define MOLPHENE_FOG_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TConfig>
class Fog {
public:
  using Color = TColor;
  using float_t = typename type_configs<TConfig>::float_type;

  enum class Type { linear, exponential };

  float_t visibility_range {0};

  Color color {0xFFFFFF};

  Type fog_type {Type::linear};

  Fog() noexcept = default;
};
} // namespace molphene

#endif
