#ifndef MOLPHENE_SPHERE_MESH_BUILDER_HPP
#define MOLPHENE_SPHERE_MESH_BUILDER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"
#include "shape/UvSphere.hpp"

namespace molphene {

template<typename TConfig>
class SphereMeshBuilder {
public:
  using size_type = typename type_configs<TConfig>::size_type;
  using float_type = typename type_configs<TConfig>::float_type;

public:
  SphereMeshBuilder(size_type lat_div, size_type long_div) noexcept
  : lat_div_{lat_div}
  , long_div_{long_div}
  {
  }

  template<typename TNormIter>
  void build(TNormIter normalit) const noexcept
  {
    const auto dir = Vec3<float_type>{0, 0, 1};
    const auto top = [&dir]() noexcept
    {
      auto top = dir.cross({0, 1, 0});
      if(top.magnitude() == 0) {
        top = {0, 0, 1};
      }
      return top.to_unit();
    }
    ();
    const auto right = top.cross(dir);

    for(auto i = size_type{0}; i < lat_div_; ++i) {
      constexpr auto pi = float{M_PI};

      const auto theta = pi / lat_div_ * i;
      const auto sin_theta = std::sin(theta);
      const auto cos_theta = std::cos(theta);

      const auto next_theta = pi / lat_div_ * (i + 1);
      const auto next_sint = std::sin(next_theta);
      const auto next_cost = std::cos(next_theta);

      for(auto j = size_type{0}; j <= long_div_; ++j) {
        const auto phi = pi * 2 * j / long_div_;
        const auto sin_phi = std::sin(phi);
        const auto cos_phi = std::cos(phi);

        const auto vx = right * cos_phi;
        const auto vy = top * sin_phi;
        const auto n = vx + vy;

        {
          const auto norm = dir * cos_theta + n * sin_theta;

          normalit = norm;
          ++normalit;

          if(j == 0) {
            normalit = norm;
            ++normalit;
          }
        }

        {
          const auto norm = dir * next_cost + n * next_sint;

          normalit = norm;
          ++normalit;

          if(j == long_div_) {
            normalit = norm;
            ++normalit;
          }
        }
      }
    }
  }

  template<typename OutputIt, typename Function>
  void build_vertices(OutputIt output, Function func) const noexcept
  {
    const auto dir = Vec3<float_type>{0, 0, 1};
    const auto top = [&dir]() noexcept
    {
      auto top = dir.cross({0, 1, 0});
      if(top.magnitude() == 0) {
        top = {0, 0, 1};
      }
      return top.to_unit();
    }
    ();
    const auto right = top.cross(dir);

    for(auto i = size_type{0}; i < lat_div_; ++i) {
      constexpr auto pi = float{M_PI};

      const auto theta = pi / lat_div_ * i;
      const auto sin_theta = std::sin(theta);
      const auto cos_theta = std::cos(theta);

      const auto next_theta = pi / lat_div_ * (i + 1);
      const auto next_sint = std::sin(next_theta);
      const auto next_cost = std::cos(next_theta);

      for(auto j = size_type{0}; j <= long_div_; ++j) {
        const auto phi = pi * 2 * j / long_div_;
        const auto sin_phi = std::sin(phi);
        const auto cos_phi = std::cos(phi);

        const auto vx = right * cos_phi;
        const auto vy = top * sin_phi;
        const auto n = vx + vy;

        {
          const auto norm = dir * cos_theta + n * sin_theta;

          *output++ = func(norm);

          if(j == 0) {
            *output++ = func(norm);
          }
        }

        {
          const auto norm = dir * next_cost + n * next_sint;

          *output++ = func(norm);

          if(j == long_div_) {
            *output++ = func(norm);
          }
        }
      }
    }
  }

  template<typename Position, typename Radius, typename OutputIt>
  void build_positions(Position pos, Radius rad, OutputIt output) const noexcept
  {
    build_vertices(
     output, [=](auto norm) noexcept { return pos + norm * rad; });
  }

  template<typename OutputIt>
  void build_normals(OutputIt output) const noexcept
  {
    build_vertices(
     output, [](auto norm) noexcept { return norm; });
  }

  template<typename Texcoord, typename OutputIt>
  void build_texcoords(Texcoord atex, OutputIt output) const noexcept
  {
    build_vertices(
     output, [=](auto) noexcept { return atex; });
  }

  auto vertices_size() const noexcept -> size_type
  {
    return lat_div_ * (long_div_ + 1) * 2 + lat_div_ * 2;
  }

private:
  size_type lat_div_;

  size_type long_div_;
};
} // namespace molphene

#endif
