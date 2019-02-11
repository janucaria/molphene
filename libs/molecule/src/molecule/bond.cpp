#include "bond.hpp"

namespace molphene {

bond::bond(int a1, int a2)
: a1_(a1)
, a2_(a2)
{
}

auto bond::atom1() const noexcept -> int
{
  return a1_;
}

auto bond::atom2() const noexcept -> int
{
  return a2_;
}

} // namespace molphene
