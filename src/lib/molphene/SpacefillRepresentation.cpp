#include "SpacefillRepresentation.hpp"

namespace molphene {

auto SpacefillRepresentation::atom_radius(
 typename Atom::Element element) const noexcept -> double
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

}