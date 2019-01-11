#ifndef MOLPHENE_MOL_BOND_HPP
#define MOLPHENE_MOL_BOND_HPP

namespace molphene {
class Bond {
public:
  Bond(int a1, int a2);

  auto atom1() -> int;

  auto atom2() -> int;

private:
  int a1_;

  int a2_;
};
} // namespace molphene

#endif
