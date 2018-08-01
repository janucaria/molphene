#ifndef MOLPHENE_DIRECTIONAL_LIGHT_HPP
#define MOLPHENE_DIRECTIONAL_LIGHT_HPP

#include "Basic_light.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
struct Directional_light : Basic_light<TColor, TVector> {
  using typename Basic_light<TColor, TVector>::Color_type;
  using typename Basic_light<TColor, TVector>::Vec3_type;
  
  Vec3_type direction{0, 0, -1};

  using Basic_light<TColor, TVector>::Basic_light;

  Directional_light() noexcept = default;
};
} // namespace molphene

#endif
