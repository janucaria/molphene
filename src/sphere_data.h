#ifndef __Molphene__sphere_data__
#define __Molphene__sphere_data__

#include <cstddef>

#include "m3d.hpp"
#include "primitive_data.h"
#include "shape/Sphere.hpp"

namespace molphene {

class sphere_data : public primitive_data<Sphere<float>, colour, Vec2f> {
public:
  sphere_data();

  void
  insert(size_t idx, Sphere<float> sphere, colour col, Vec2f tex) override;

  unsigned int
  unitlen() const override;

  void
  reserve(size_t n) override;

  void
  clear() override;

  const Vec2f*
  texcoords();

private:
  unsigned int londiv_;

  unsigned int latdiv_;

  Vec2f* texcoords_;
};
} // namespace molphene

#endif
