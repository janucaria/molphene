#include "SpacefillRepresentation.hpp"

namespace molphene {

auto SpacefillRepresentation::atom_radius(typename Atom::Element element) const
 noexcept -> double
{
  switch(radius_type) {
  case AtomRadiusType::van_der_waals:
    return element.rvdw;
  case AtomRadiusType::covalent:
    return element.rcov;
  default:
    return radius_size;
  }
}

auto SpacefillRepresentation::atom_color(const Atom& atom) const noexcept
 -> Rgba8
{
  return color_manager.get_element_color(atom.element().symbol);
}

void SpacefillRepresentation::clear_buffers() noexcept
{
  atom_sphere_buffer.reset(nullptr);
}

} // namespace molphene