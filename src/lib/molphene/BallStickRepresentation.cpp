#include "BallStickRepresentation.hpp"

namespace molphene {

auto BallStickRepresentation::atom_radius(typename Atom::Element element) const
 noexcept -> double
{
  switch(atom_radius_type) {
  case AtomRadiusType::van_der_waals:
    return element.rvdw * radius_size;
  case AtomRadiusType::covalent:
    return element.rcov * radius_size;
  default:
    return radius_size;
  }
}

auto BallStickRepresentation::atom_color(const Atom& atom) const noexcept
 -> Rgba8
{
  return color_manager.get_element_color(atom.element().symbol);
}

void BallStickRepresentation::clear_buffers() noexcept
{
  atom_sphere_buffer.reset(nullptr);

  bond1_cylinder_buffer.reset(nullptr);

  bond2_cylinder_buffer.reset(nullptr);
}

} // namespace molphene
