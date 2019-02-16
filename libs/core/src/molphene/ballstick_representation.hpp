#ifndef MOLPHENE_BALL_STICK_REPRESENTATION_HPP
#define MOLPHENE_BALL_STICK_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "color_light_buffer.hpp"
#include "color_light_shader.hpp"
#include "color_manager.hpp"
#include "m3d.hpp"

#include <molecule/atom.hpp>
#include <molecule/atom_radius_kind.hpp>

namespace molphene {

class ballstick_representation {
public:
  atom_radius_kind atom_radius_type{atom_radius_kind::fixed};

  double radius_size{0.25};

  color_manager color_manager;

  std::unique_ptr<color_light_buffer> atom_sphere_buffer;

  std::unique_ptr<color_light_buffer> bond1_cylinder_buffer;

  std::unique_ptr<color_light_buffer> bond2_cylinder_buffer;

  auto atom_radius(typename atom::atom_element element) const noexcept
   -> double;

  auto atom_color(const atom& atom) const noexcept -> rgba8;

  void clear_buffers() noexcept;

  void render(const color_light_shader& shader) const noexcept;
};

} // namespace molphene

#endif
