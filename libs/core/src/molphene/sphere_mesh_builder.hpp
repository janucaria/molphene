#ifndef MOLPHENE_SPHERE_MESH_BUILDER_HPP
#define MOLPHENE_SPHERE_MESH_BUILDER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"

namespace molphene {

template<std::size_t VLatDivs, std::size_t VLongDivs, typename TConfig = void>
class sphere_mesh_builder {
public:
  using size_type = std::size_t;
  using float_type = typename type_configs<TConfig>::float_type;

  static constexpr auto latitude_divs = VLatDivs;
  static constexpr auto longitude_divs = VLatDivs;

public:

  template<typename OutputIt, typename Function>
  constexpr void build_vertices(OutputIt output, Function func) const noexcept
  {
    const auto dir = vec3<float_type>{0, 0, 1};
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

    for(auto i = size_type{0}; i < latitude_divs; ++i) {
      constexpr auto pi = M_PI;

      const auto theta = pi / latitude_divs * i;
      const auto sin_theta = std::sin(theta);
      const auto cos_theta = std::cos(theta);

      const auto next_theta = pi / latitude_divs * (i + 1);
      const auto next_sint = std::sin(next_theta);
      const auto next_cost = std::cos(next_theta);

      for(auto j = size_type{0}; j <= longitude_divs; ++j) {
        const auto phi = pi * 2 * j / longitude_divs;
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

          if(j == longitude_divs) {
            *output++ = func(norm);
          }
        }
      }
    }
  }

  template<typename Sph, typename OutputIt>
  constexpr void build_positions(Sph sphere, OutputIt output) const noexcept
  {
    build_vertices(
     output, [=](auto norm) noexcept {
       return sphere.center + norm * sphere.radius;
     });
  }

  template<typename OutputIt>
  constexpr void build_normals(OutputIt output) const noexcept
  {
    build_vertices(
     output, [](auto norm) noexcept { return norm; });
  }

  template<typename Texcoord, typename OutputIt>
  constexpr void build_texcoords(Texcoord atex, OutputIt output) const noexcept
  {
    build_vertices(
     output, [=](auto) noexcept { return atex; });
  }

  constexpr auto vertices_size() const noexcept -> size_type
  {
    return latitude_divs * (longitude_divs + 1) * 2 + latitude_divs * 2;
  }
};
} // namespace molphene

#endif
