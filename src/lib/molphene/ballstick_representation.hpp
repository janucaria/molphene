#ifndef MOLPHENE_BALL_STICK_REPRESENTATION_HPP
#define MOLPHENE_BALL_STICK_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "color_light_buffer.hpp"
#include "color_manager.hpp"
#include "m3d.hpp"

#include <molecule/Atom.hpp>
#include <molecule/AtomRadiusType.hpp>

namespace molphene {

class ballstick_representation {
public:
  AtomRadiusType atom_radius_type{AtomRadiusType::fixed};

  double radius_size{0.25};

  color_manager color_manager;

  std::unique_ptr<color_light_buffer> atom_sphere_buffer;

  std::unique_ptr<color_light_buffer> bond1_cylinder_buffer;

  std::unique_ptr<color_light_buffer> bond2_cylinder_buffer;

  auto atom_radius(typename Atom::Element element) const noexcept -> double;

  auto atom_color(const Atom& atom) const noexcept -> rgba8;

  void clear_buffers() noexcept;
};

} // namespace molphene

#endif
