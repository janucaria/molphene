#ifndef MOLPHENE_FOG_HPP
#define MOLPHENE_FOG_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TScalar = float>
class Fog {
public:
  using Color = TColor;
  using Scalar = TScalar;

  enum class Type { linear, exponential };

  Scalar visibility_range{0};

  Color color{0xFFFFFF};

  Type fog_type{Type::linear};

  Fog() noexcept = default;
};
} // namespace molphene

#endif
