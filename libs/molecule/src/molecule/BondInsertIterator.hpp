#ifndef MOLPHENE_MOLECULE_BOND_INSERT_ITERATOR_HPP
#define MOLPHENE_MOLECULE_BOND_INSERT_ITERATOR_HPP

#include "stdafx.hpp"

#include "Bond.hpp"

namespace molphene {

template<typename Container>
struct BondInsertIterator {
  using container_type = Container;

  using value_type = void;
  using difference_type = void;
  using pointer = void;
  using reference = void;
  using iterator_category = std::output_iterator_tag;

  explicit BondInsertIterator(container_type& container) noexcept
  : container_{container}
  {
  }

  auto operator=(const Bond& atom) -> BondInsertIterator&
  {
    container_.add_bond(atom);
    return *this;
  }

  auto operator*() -> BondInsertIterator&
  {
    return *this;
  }

  auto operator++() -> BondInsertIterator&
  {
    return *this;
  }

  auto operator++(int) -> BondInsertIterator&
  {
    return *this;
  }

private:
  container_type& container_;
};

} // namespace molphene

#endif
