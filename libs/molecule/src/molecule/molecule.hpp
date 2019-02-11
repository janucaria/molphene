#ifndef MOLPHENE_MOLECULE_MOLECULE_HPP
#define MOLPHENE_MOLECULE_MOLECULE_HPP

#include <vector>

#include "atom.hpp"
#include "bond.hpp"

namespace molphene {
class molecule {
public:
  using atoms_type = std::vector<atom>;
  using bonds_type = std::vector<bond>;

  auto atoms() const noexcept -> const atoms_type&;

  auto bonds() const noexcept -> const bonds_type&;

  void add_atom(const atom& atom);

  void add_bond(const bond& bond);

private:
  atoms_type atoms_;

  bonds_type bonds_;
};

} // namespace molphene

#endif
