#ifndef MOLPHENE_SHAPE_SPHERE_HPP
#define MOLPHENE_SHAPE_SPHERE_HPP

#include "../m3d.hpp"

namespace molphene {

template<typename TRadii, typename TCenter = Vec3<TRadii>>
class Sphere {
public:
  using Radius = TRadii;
  using Center = TCenter;

  Radius radius{0};
  Center center{0, 0, 0};

  Sphere() noexcept = default;

  explicit Sphere(Radius radii) noexcept
  : radius{radii}
  {
  }

  Sphere(Radius radii, Center center) noexcept
  : radius{radii}
  , center{center}
  {
  }
};

} // namespace molphene

#endif