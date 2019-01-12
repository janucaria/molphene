#ifndef MOLPHENE_MOL_MOLECULE_HPP
#define MOLPHENE_MOL_MOLECULE_HPP

#include <vector>

#include "Atom.hpp"
#include "Bond.hpp"

namespace molphene {
class Molecule {
public:
  using atoms_type = std::vector<Atom>;
  using bonds_type = std::vector<Bond>;

  auto atoms() noexcept -> atoms_type&;

  auto bonds() noexcept -> bonds_type&;

  void add_atom(const Atom& atom);

  void add_bond(const Bond& bond);

private:
  std::vector<Atom> atoms_;

  std::vector<Bond> bonds_;
};

} // namespace molphene

#endif
