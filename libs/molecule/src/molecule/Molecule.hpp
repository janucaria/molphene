#ifndef MOLPHENE_MOLECULE_MOLECULE_HPP
#define MOLPHENE_MOLECULE_MOLECULE_HPP

#include <vector>

#include "Atom.hpp"
#include "Bond.hpp"

namespace molphene {
class Molecule {
public:
  using atoms_type = std::vector<Atom>;
  using bonds_type = std::vector<Bond>;

  auto atoms() const noexcept -> const atoms_type&;

  auto bonds() const noexcept -> const bonds_type&;

  void add_atom(const Atom& atom);

  void add_bond(const Bond& bond);

private:
  atoms_type atoms_;

  bonds_type bonds_;
};

} // namespace molphene

#endif
