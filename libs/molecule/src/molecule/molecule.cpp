#include "molecule.hpp"

namespace molphene {

auto molecule::atoms() const noexcept -> const atoms_type&
{
  return atoms_;
}

auto molecule::bonds() const noexcept -> const bonds_type&
{
  return bonds_;
}

void molecule::add_atom(const atom& atom)
{
  atoms_.push_back(atom);
}

void molecule::add_bond(const bond& bond)
{
  bonds_.push_back(bond);
}

} // namespace molphene
