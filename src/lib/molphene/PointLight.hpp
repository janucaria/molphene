#ifndef MOLPHENE_POINT_LIGHT_HPP
#define MOLPHENE_POINT_LIGHT_HPP

#include "BasicLight.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
struct PointLight : BasicLight<TColor, TVector> {
  using typename BasicLight<TColor, TVector>::Color;
  using typename BasicLight<TColor, TVector>::Vec3;

  float radius{100};

  Vec3 attenuation{1, 0, 0};

  Vec3 location{0, 0, 0};

  using BasicLight<TColor, TVector>::BasicLight;

  PointLight() noexcept = default;
};
} // namespace molphene

#endif
