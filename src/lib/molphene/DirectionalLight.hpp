#ifndef MOLPHENE_DIRECTIONAL_LIGHT_HPP
#define MOLPHENE_DIRECTIONAL_LIGHT_HPP

#include "BasicLight.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
struct DirectionalLight : BasicLight<TColor, TVector> {
  using typename BasicLight<TColor, TVector>::Color;
  using typename BasicLight<TColor, TVector>::Vec3;
  
  Vec3 direction{0, 0, -1};

  using BasicLight<TColor, TVector>::BasicLight;

  DirectionalLight() noexcept = default;
};
} // namespace molphene

#endif
