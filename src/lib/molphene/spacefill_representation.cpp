#include "spacefill_representation.hpp"

namespace molphene {

auto spacefill_representation::atom_radius(typename Atom::Element element) const
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

auto spacefill_representation::atom_color(const Atom& atom) const noexcept
 -> rgba8
{
  return color_manager.get_element_color(atom.element().symbol);
}

void spacefill_representation::clear_buffers() noexcept
{
  atom_sphere_buffer.reset(nullptr);
}

} // namespace molphene