#include "stdafx.hpp"

#include "SphereMeshBuilder.hpp"

namespace molphene {

SphereMeshBuilder::SphereMeshBuilder(size_t max_bytes,
                                         Div_type lat_div,
                                         Div_type long_div)
: lat_div_{lat_div}
, long_div_{long_div}
{
  const auto vertices_per_model = get_vertices_size();
  const auto bytes_per_vertex = size_bytes();
  const auto bytes_per_model = bytes_per_vertex * vertices_per_model;
  size_ = max_bytes / bytes_per_model;
  const auto total_vertices = size_ * vertices_per_model;

  positions_.reserve(total_vertices);
  normals_.reserve(total_vertices);
  texcoords_.reserve(total_vertices);
}

size_t
SphereMeshBuilder::size()
{
  return size_;
}

size_t
SphereMeshBuilder::get_vertices_size()
{
  return lat_div_ * (long_div_ + 1) * 2 + lat_div_ * 2;
}

size_t
SphereMeshBuilder::size_bytes()
{
  return sizeof(Vec3f) * 2 + sizeof(Vec2f);
}

const std::vector<Vec3f>&
SphereMeshBuilder::positions() const noexcept
{
  return positions_;
}

const std::vector<Vec3f>&
SphereMeshBuilder::normals() const noexcept
{
  return normals_;
}

const std::vector<Vec2f>&
SphereMeshBuilder::texcoords() const noexcept
{
  return texcoords_;
}

UvSphere<float>
SphereMeshBuilder::sphere(UvSphere<float> sphere)
{
  return sphere_ = sphere;
}

void
SphereMeshBuilder::build(size_t idx)
{
  const auto dir = sphere_.axis.to_unit();
  const auto top = [&dir]() {
    auto top = dir.cross({0, 1, 0});
    if(top.magnitude() == 0) {
      top = {0, 0, 1};
    }
    return top.to_unit();
  }();
  const auto right = top.cross(dir);

  const auto rad = sphere_.radius;
  const auto pos = sphere_.center;

  const auto vert_size = get_vertices_size();

  auto positions2 = std::vector<Vec3f>(vert_size);
  auto normals2 = std::vector<Vec3f>(vert_size);
  auto texcoords2 = std::vector<Vec2f>(vert_size);

  idx *= get_vertices_size();
  for(auto i = Div_type{0}; i < lat_div_; ++i) {
    constexpr auto pi = float{M_PI};

    const auto theta = pi / lat_div_ * i;
    const auto sin_theta = std::sin(theta);
    const auto cos_theta = std::cos(theta);

    const auto next_theta = pi / lat_div_ * (i + 1);
    const auto next_sint = std::sin(next_theta);
    const auto next_cost = std::cos(next_theta);

    for(auto j = Div_type{0}; j <= long_div_; ++j) {
      const auto phi = pi * 2 * j / long_div_;
      const auto sin_phi = std::sin(phi);
      const auto cos_phi = std::cos(phi);

      const auto vx = right * cos_phi;
      const auto vy = top * sin_phi;
      const auto n = vx + vy;

      auto norm = dir * cos_theta + n * sin_theta;

      positions_[idx] = pos + norm * rad;
      normals_[idx] = norm;
      texcoords_[idx] = tex_;

      positions2.emplace_back(pos + norm * rad);
      normals2.emplace_back(norm);
      texcoords2.emplace_back(tex_);

      idx++;

      if(j == 0) {
        positions_[idx] = pos + norm * rad;
        normals_[idx] = norm;
        texcoords_[idx] = tex_;

        positions2.emplace_back(pos + norm * rad);
        normals2.emplace_back(norm);
        texcoords2.emplace_back(tex_);

        idx++;
      }

      norm = dir * next_cost + n * next_sint;

      positions_[idx] = pos + norm * rad;
      normals_[idx] = norm;
      texcoords_[idx] = tex_;

      positions2.emplace_back(pos + norm * rad);
      normals2.emplace_back(norm);
      texcoords2.emplace_back(tex_);

      idx++;

      if(j == long_div_) {
        positions_[idx] = pos + norm * rad;
        normals_[idx] = norm;
        texcoords_[idx] = tex_;

        positions2.emplace_back(pos + norm * rad);
        normals2.emplace_back(norm);
        texcoords2.emplace_back(tex_);

        idx++;
      }
    }
  }
}

} // namespace molphene
