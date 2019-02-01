#include "Bond.hpp"

namespace molphene {

Bond::Bond(int a1, int a2)
: a1_(a1)
, a2_(a2)
{
}

auto Bond::atom1() const noexcept -> int
{
  return a1_;
}

auto Bond::atom2() const noexcept -> int
{
  return a2_;
}

} // namespace molphene
