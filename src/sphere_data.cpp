#include "sphere_data.h"

namespace molphene {

sphere_data::sphere_data()
: primitive_data()
, londiv_(10)
, latdiv_(20)
{
}

unsigned int
sphere_data::unitlen() const
{
  return londiv_ * (latdiv_ + 1) * 2 + londiv_ * 2;
}
void
sphere_data::reserve(size_t n)
{
  primitive_data::reserve(n);
  size_t totalvers = n * unitlen();
  texcoords_ = new Vec2f[totalvers];
}
void
sphere_data::clear()
{
  primitive_data::clear();
  delete[] texcoords_;
  texcoords_ = nullptr;
}

const Vec2f*
sphere_data::texcoords()
{
  return texcoords_;
}

void
sphere_data::insert(size_t idx, Sphere<float> sphere, colour col, Vec2f tex)
{
  const auto pos = sphere.center;
  const auto rad = sphere.radius;
  for(unsigned int i = 0; i < londiv_; ++i) {
    float theta = 1.0f * i * M_PI / londiv_;
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);

    float nextTheta = 1.0f * (i + 1) * M_PI / londiv_;
    float nextSinTheta = sin(nextTheta);
    float nextCosTheta = cos(nextTheta);

    for(unsigned int j = 0; j <= latdiv_; ++j) {
      float phi = 2.0f * M_PI * j / latdiv_;
      float sinPhi = sin(phi);
      float cosPhi = cos(phi);

      vec3f norm(cosPhi * sinTheta, sinPhi * sinTheta, cosTheta);

      positions_[idx] = pos + norm * rad;
      normals_[idx] = norm;
      colors_[idx] = col;
      texcoords_[idx] = tex;
      idx++;

      if(j == 0) {
        positions_[idx] = positions_[idx - 1];
        normals_[idx] = normals_[idx - 1];
        colors_[idx] = colors_[idx - 1];
        texcoords_[idx] = tex;
        idx++;
      }

      norm = {cosPhi * nextSinTheta, sinPhi * nextSinTheta, nextCosTheta};

      positions_[idx] = pos + norm * rad;
      normals_[idx] = norm;
      colors_[idx] = col;
      texcoords_[idx] = tex;
      idx++;

      if(j == latdiv_) {
        positions_[idx] = positions_[idx - 1];
        normals_[idx] = normals_[idx - 1];
        colors_[idx] = colors_[idx - 1];
        texcoords_[idx] = tex;
        idx++;
      }
    }
  }
}

} // namespace molphene