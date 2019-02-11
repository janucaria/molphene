#ifndef MOLPHENE_SPACEFILL_REPRESENTATION_HPP
#define MOLPHENE_SPACEFILL_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "color_light_buffer.hpp"
#include "color_manager.hpp"
#include "m3d.hpp"
#include <molecule/atom.hpp>
#include <molecule/atom_radius_kind.hpp>

namespace molphene {

class spacefill_representation {
public:
  atom_radius_kind radius_type{atom_radius_kind::van_der_waals};

  double radius_size{1};

  color_manager color_manager;

  std::unique_ptr<color_light_buffer> atom_sphere_buffer;

  auto atom_radius(typename atom::atom_element element) const noexcept -> double;

  auto atom_color(const atom& atom) const noexcept -> rgba8;

  void clear_buffers() noexcept;
};

} // namespace molphene

#endif
