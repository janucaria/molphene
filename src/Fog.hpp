#ifndef MOLPHENE_FOG_HPP
#define MOLPHENE_FOG_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TScalar = float>
class Fog {
public:
  using Color_type = TColor;
  using Scalar_type = TScalar;

  enum class Type {
    linear,
    exponential
  };

  Scalar_type visibility_range{0};

  Color_type color{0xFFFFFF};

  Type fog_type{Type::linear};

  Fog() noexcept = default;
};
} // namespace molphene

#endif
