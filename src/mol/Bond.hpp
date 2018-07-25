#ifndef MOLPHENE_MOL_BOND_HPP
#define MOLPHENE_MOL_BOND_HPP

#include "Atom.hpp"

namespace molphene {
class Bond {
public:
  Bond(Atom& a1, Atom& a2);

  Atom&
  atom1();

  Atom&
  atom2();

private:
  Atom* a1_;

  Atom* a2_;
};
} // namespace molphene

#endif
