#include "Molecule.hpp"

namespace molphene {

auto Molecule::atoms() const noexcept -> const atoms_type&
{
  return atoms_;
}

auto Molecule::bonds() const noexcept -> const bonds_type&
{
  return bonds_;
}

void Molecule::add_atom(const Atom& atom)
{
  atoms_.push_back(atom);
}

void Molecule::add_bond(const Bond& bond)
{
  bonds_.push_back(bond);
}

} // namespace molphene
