#ifndef MOLPHENE_SPACEFILL_REPRESENTATION_HPP
#define MOLPHENE_SPACEFILL_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "color_light_buffer.hpp"
#include "color_manager.hpp"
#include "m3d.hpp"
#include <molecule/Atom.hpp>
#include <molecule/AtomRadiusType.hpp>

namespace molphene {

class spacefill_representation {
public:
  AtomRadiusType radius_type{AtomRadiusType::van_der_waals};

  double radius_size{1};

  color_manager color_manager;

  std::unique_ptr<color_light_buffer> atom_sphere_buffer;

  auto atom_radius(typename Atom::Element element) const noexcept -> double;

  auto atom_color(const Atom& atom) const noexcept -> rgba8;

  void clear_buffers() noexcept;
};

} // namespace molphene

#endif
