#ifndef __Molphene__sphere_data__
#define __Molphene__sphere_data__

#include <cstddef>

#include "m3d.hpp"
#include "shape/Sphere.hpp"
#include "primitive_data.h"

namespace molphene {

class sphere_data : public primitive_data<Sphere<float>, colour> {
public:
  sphere_data();

  void
  insert(size_t idx, Sphere<float> sphere, colour col) override;

  unsigned int
  unitlen() const override;

private:
  unsigned int londiv_;

  unsigned int latdiv_;
};
} // namespace molphene

#endif
