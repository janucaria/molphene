#include "Bond.hpp"

namespace molphene {

Bond::Bond(Atom& a1, Atom& a2)
: a1_(&a1)
, a2_(&a2)
{
}

Atom&
Bond::atom1()
{
  return *a1_;
}

Atom&
Bond::atom2()
{
  return *a2_;
}

} // namespace molphene
