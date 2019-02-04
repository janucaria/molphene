#ifndef MOLPHENE_SPACEFILL_REPRESENTATION_HPP
#define MOLPHENE_SPACEFILL_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "ColorLightBuffer.hpp"
#include "ColourManager.hpp"
#include "m3d.hpp"
#include "mol/Atom.hpp"
#include "mol/AtomRadiusType.hpp"

namespace molphene {

class SpacefillRepresentation {
public:
  AtomRadiusType radius_type{AtomRadiusType::van_der_waals};

  double radius_size{1};

  ColourManager color_manager;

  std::unique_ptr<ColorLightBuffer> atom_sphere_buffer;

  auto atom_radius(typename Atom::Element element) const noexcept -> double;

  auto atom_color(const Atom& atom) const noexcept -> Rgba8;

  void clear_buffers() noexcept;
};

} // namespace molphene

#endif
