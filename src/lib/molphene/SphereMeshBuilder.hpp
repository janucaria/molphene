#ifndef MOLPHENE_SPHERE_MESH_BUILDER_HPP
#define MOLPHENE_SPHERE_MESH_BUILDER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"
#include "shape/UvSphere.hpp"

namespace molphene {

template<typename TConfig>
class SphereMeshBuilder {
public:
  using size_t = typename type_configs<TConfig>::size_type;
  using float_t = typename type_configs<TConfig>::float_type;
  using Vec3f = Vec3<float>;
  using Vec2f = Vec2<float>;

public:
  SphereMeshBuilder(size_t max_bytes, size_t lat_div, size_t long_div) noexcept
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

  void
  build(size_t idx) noexcept
  {
    const auto dir = sphere_.axis.to_unit();
    const auto top = [&dir]() noexcept {
      auto top = dir.cross({0, 1, 0});
      if(top.magnitude() == 0) {
        top = {0, 0, 1};
      }
      return top.to_unit();
    }();
    const auto right = top.cross(dir);

    const auto rad = sphere_.radius;
    const auto pos = sphere_.center;

    idx *= get_vertices_size();
    for(auto i = size_t{0}; i < lat_div_; ++i) {
      constexpr auto pi = float{M_PI};

      const auto theta = pi / lat_div_ * i;
      const auto sin_theta = std::sin(theta);
      const auto cos_theta = std::cos(theta);

      const auto next_theta = pi / lat_div_ * (i + 1);
      const auto next_sint = std::sin(next_theta);
      const auto next_cost = std::cos(next_theta);

      for(auto j = size_t{0}; j <= long_div_; ++j) {
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

        idx++;

        if(j == 0) {
          positions_[idx] = pos + norm * rad;
          normals_[idx] = norm;
          texcoords_[idx] = tex_;

          idx++;
        }

        norm = dir * next_cost + n * next_sint;

        positions_[idx] = pos + norm * rad;
        normals_[idx] = norm;
        texcoords_[idx] = tex_;

        idx++;

        if(j == long_div_) {
          positions_[idx] = pos + norm * rad;
          normals_[idx] = norm;
          texcoords_[idx] = tex_;

          idx++;
        }
      }
    }
  }

  size_t
  get_vertices_size() const noexcept
  {
    return lat_div_ * (long_div_ + 1) * 2 + lat_div_ * 2;
  }

  size_t
  size_bytes() const noexcept
  {
    return sizeof(Vec3f) * 2 + sizeof(Vec2f);
  }

  size_t
  size() const noexcept
  {
    return size_;
  }

  const std::vector<Vec3f>&
  positions() const noexcept
  {
    return positions_;
  }

  const std::vector<Vec3f>&
  normals() const noexcept
  {
    return normals_;
  }

  const std::vector<Vec2f>&
  texcoords() const noexcept
  {
    return texcoords_;
  }

  template<typename... Ts>
  Vec2f
  texcoord(Ts&&... args) noexcept
  {
    return tex_ = Vec2f{std::forward<Ts>(args)...};
  }

  UvSphere<float_t>
  sphere(UvSphere<float_t> sphere) noexcept
  {
    return sphere_ = sphere;
  }

private:
  size_t lat_div_;

  size_t long_div_;

  std::vector<Vec3f> normals_;

  std::vector<Vec3f> positions_;

  std::vector<Vec2f> texcoords_;

  size_t size_;

  Vec2f tex_{0};

  UvSphere<float_t> sphere_;
};
} // namespace molphene

#endif
