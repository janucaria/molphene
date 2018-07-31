#ifndef MOLPHENE_POINT_LIGHT_HPP
#define MOLPHENE_POINT_LIGHT_HPP

#include "m3d.hpp"

namespace molphene {

template<typename TColor, typename TVector>
class Point_light {
public:
  using Color_type = TColor;
  using Vec3_type = TVector;

  float ambient_intensity{0};

  float intensity{1};
  
  float radius{100};
  
  Color_type color{0xFFFFFF};

  Vec3_type attenuation{1, 0, 0};

  Vec3_type location{0, 0, 0};

  Point_light() noexcept = default;
};
} // namespace molphene

#endif
