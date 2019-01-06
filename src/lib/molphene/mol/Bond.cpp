#include "Bond.hpp"

namespace molphene {

Bond::Bond(Atom& a1, Atom& a2)
: a1_(&a1)
, a2_(&a2)
{
}

auto Bond::atom1() -> Atom&
{
  return *a1_;
}

auto Bond::atom2() -> Atom&
{
  return *a2_;
}

} // namespace molphene
