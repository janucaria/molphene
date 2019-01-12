#ifndef MOLPHENE_BOND_INSERTER_ITERATOR_HPP
#define MOLPHENE_BOND_INSERTER_ITERATOR_HPP

#include "../stdafx.hpp"

namespace molphene {

template<typename Container>
struct BondInserterIterator {
  using container_type = Container;

  using value_type = void;
  using difference_type = void;
  using pointer = void;
  using reference = void;
  using iterator_category = std::output_iterator_tag;

  explicit BondInserterIterator(container_type& container) noexcept
  : container_{container}
  {
  }

  auto operator=(const Bond& atom) -> BondInserterIterator&
  {
    container_.add_bond(atom);
    return *this;
  }

  auto operator*() -> BondInserterIterator&
  {
    return *this;
  }

  auto operator++() -> BondInserterIterator&
  {
    return *this;
  }

  auto operator++(int) -> BondInserterIterator&
  {
    return *this;
  }

private:
  container_type& container_;
};

} // namespace molphene

#endif
