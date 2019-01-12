#include "Molecule.hpp"

namespace molphene {

  auto Molecule::atoms() noexcept -> atoms_type&
  {
    return atoms_;
  }

  auto Molecule::bonds() noexcept -> bonds_type&
  {
    return bonds_;
  }

  void Molecule::atoms(atoms_type&& atoms)
  {
    atoms_ = std::move(atoms);
  }

  void Molecule::bonds(bonds_type&& bonds)
  {
    bonds_ = std::move(bonds);
  }

} // namespace molphene
