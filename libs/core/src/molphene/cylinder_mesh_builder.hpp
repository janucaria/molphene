#ifndef MOLPHENE_CYLINDER_MESH_BUILDER_HPP
#define MOLPHENE_CYLINDER_MESH_BUILDER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"

namespace molphene {

template<typename TCylinder>
struct build_cylinder_mesh_position_params {
  TCylinder cylinder;

  constexpr explicit build_cylinder_mesh_position_params(
   TCylinder cylinder) noexcept
  : cylinder{cylinder}
  {
  }
};

template<typename TCylinder>
struct build_cylinder_mesh_normal_params {
  TCylinder cylinder;

  constexpr explicit build_cylinder_mesh_normal_params(
   TCylinder cylinder) noexcept
  : cylinder{cylinder}
  {
  }
};

template<typename TCylinder, typename TVertex>
struct build_cylinder_mesh_fill_params {
  TCylinder cylinder;
  TVertex vertex;

  constexpr build_cylinder_mesh_fill_params(TCylinder cylinder,
                                            TVertex vertex) noexcept
  : cylinder{cylinder}
  , vertex{vertex}
  {
  }
};

template<std::size_t VBands, typename TConfig = void>
class cylinder_mesh_builder {
public:
  using size_type = std::size_t;
  using float_type = typename type_configs<TConfig>::float_type;

  static constexpr auto bands = VBands;

public:
  template<typename Cyl, typename OutputIt, typename Function>
  constexpr void build_vertices(Cyl cyl, OutputIt output, Function func) const
   noexcept
  {
    const auto cyl_top = cyl.top;
    const auto cyl_bottom = cyl.bottom;
    const auto dir = (cyl_bottom - cyl_top).to_unit();
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

    constexpr auto pi = M_PI;
    for(auto i = size_type{0}; i <= bands; ++i) {
      const auto theta = pi * 2 * i / bands;
      const auto sin_theta = std::sin(theta);
      const auto cos_theta = std::cos(theta);

      const auto vx = right * cos_theta;
      const auto vy = top * sin_theta;
      const auto n = vx + vy;

      {
        const auto pos = cyl_bottom;
        const auto norm = dir;

        *output++ = func(pos, norm);

        if(i == 0) {
          *output++ = func(pos, norm);
        }
      }

      {
        const auto pos = cyl_bottom + n * cyl.radius;
        const auto norm = dir;

        *output++ = func(pos, norm);

        if(i == bands) {
          *output++ = func(pos, norm);
        }
      }
    }

    for(auto i = size_type{0}; i <= bands; ++i) {
      const auto theta = pi * 2 * i / bands;
      const auto sin_theta = std::sin(theta);
      const auto cos_theta = std::cos(theta);

      const auto vx = right * cos_theta;
      const auto vy = top * sin_theta;
      const auto n = vx + vy;

      {
        const auto pos = cyl_bottom + n * cyl.radius;
        const auto norm = n;

        *output++ = func(pos, norm);

        if(i == 0) {
          *output++ = func(pos, norm);
        }
      }

      {
        const auto pos = cyl_top + n * cyl.radius;
        const auto norm = n;

        *output++ = func(pos, norm);

        if(i == bands) {
          *output++ = func(pos, norm);
        }
      }
    }

    for(auto i = size_type{0}; i <= bands; ++i) {
      const auto theta = pi * 2 * i / bands;
      const auto sin_theta = std::sin(theta);
      const auto cos_theta = std::cos(theta);

      const auto vx = right * cos_theta;
      const auto vy = top * sin_theta;
      const auto n = vx + vy;

      {
        const auto pos = cyl_top + n * cyl.radius;
        const auto norm = -dir;

        *output++ = func(pos, norm);

        if(i == 0) {
          *output++ = func(pos, norm);
        }
      }

      {
        const auto pos = cyl_top;
        const auto norm = -dir;

        *output++ = func(pos, norm);

        if(i == bands) {
          *output++ = func(pos, norm);
        }
      }
    }
  }

  template<typename Cyl, typename OutputIt>
  constexpr void build_positions(Cyl cyl, OutputIt output) const noexcept
  {
    build_vertices(
     cyl, output, [=](auto pos, auto) noexcept { return pos; });
  }

  template<typename TCyl, typename OutputIt>
  constexpr void build(build_cylinder_mesh_position_params<TCyl> cyl,
                       OutputIt output) const noexcept
  {
    return build_positions(cyl.cylinder, output);
  }

  template<typename Cyl, typename OutputIt>
  constexpr void build_normals(Cyl cyl, OutputIt output) const noexcept
  {
    build_vertices(
     cyl, output, [](auto, auto norm) noexcept { return norm; });
  }

  template<typename TCyl, typename OutputIt>
  constexpr void build(build_cylinder_mesh_normal_params<TCyl> cyl,
                       OutputIt output) const noexcept
  {
    return build_normals(cyl.cylinder, output);
  }

  template<typename Cyl, typename Texcoord, typename OutputIt>
  constexpr void build_texcoords(Cyl cyl, Texcoord atex, OutputIt output) const
   noexcept
  {
    build_vertices(
     cyl, output, [=](auto, auto) noexcept { return atex; });
  }

  template<typename Cyl, typename Texcoord, typename OutputIt>
  constexpr void build(build_cylinder_mesh_fill_params<Cyl, Texcoord> params,
                       OutputIt output) const noexcept
  {
    build_vertices(
     params.cylinder, output, [vert = params.vertex](auto, auto) noexcept {
       return vert;
     });
  }

  constexpr auto vertices_size() const noexcept -> size_type
  {
    return ((bands + 1) * 2 + 2) * 3;
  }
};
} // namespace molphene

#endif
