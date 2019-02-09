#ifndef MOLPHENE_BALL_STICK_REPRESENTATION_HPP
#define MOLPHENE_BALL_STICK_REPRESENTATION_HPP

#include "stdafx.hpp"

#include "ColorLightBuffer.hpp"
#include "ColourManager.hpp"
#include "m3d.hpp"

#include <molecule/Atom.hpp>
#include <molecule/AtomRadiusType.hpp>

namespace molphene {

class BallStickRepresentation {
public:
  AtomRadiusType atom_radius_type{AtomRadiusType::fixed};

  double radius_size{0.25};

  ColourManager color_manager;

  std::unique_ptr<ColorLightBuffer> atom_sphere_buffer;

  std::unique_ptr<ColorLightBuffer> bond1_cylinder_buffer;

  std::unique_ptr<ColorLightBuffer> bond2_cylinder_buffer;

  auto atom_radius(typename Atom::Element element) const noexcept -> double;

  auto atom_color(const Atom& atom) const noexcept -> Rgba8;

  void clear_buffers() noexcept;
};

} // namespace molphene

#endif
