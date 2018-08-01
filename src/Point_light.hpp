#ifndef MOLPHENE_POINT_LIGHT_HPP
#define MOLPHENE_POINT_LIGHT_HPP

#include "Basic_light.hpp"
#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
struct Point_light : Basic_light<TColor, TVector>{
  using typename Basic_light<TColor, TVector>::Color_type;
  using typename Basic_light<TColor, TVector>::Vec3_type;
  
  float radius{100};
  
  Vec3_type attenuation{1, 0, 0};

  Vec3_type location{0, 0, 0};

  using Basic_light<TColor, TVector>::Basic_light;

  Point_light() noexcept = default;
};
} // namespace molphene

#endif
