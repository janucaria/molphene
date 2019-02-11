#ifndef MOLPHENE_MOLECULE_BOND_HPP
#define MOLPHENE_MOLECULE_BOND_HPP

namespace molphene {
class bond {
public:
  bond(int a1, int a2);

  auto atom1() const noexcept -> int;

  auto atom2() const noexcept -> int;

private:
  int a1_;

  int a2_;
};
} // namespace molphene

#endif
