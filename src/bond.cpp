#include "bond.h"

namespace molphene {
bond::bond(atom& a1, atom& a2)
: a1_(a1)
, a2_(a2)
{
}

atom&
bond::getAtom1()
{
  return a1_;
}

atom&
bond::getAtom2()
{
  return a2_;
}

} // namespace molphene