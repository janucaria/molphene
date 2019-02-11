#ifndef MOLPHENE_MOLECULE_BOND_INSERT_ITERATOR_HPP
#define MOLPHENE_MOLECULE_BOND_INSERT_ITERATOR_HPP

#include "stdafx.hpp"

#include "bond.hpp"

namespace molphene {

template<typename TContainer>
struct bond_insert_iterator {
  using container_type = TContainer;

  using value_type = void;
  using difference_type = void;
  using pointer = void;
  using reference = void;
  using iterator_category = std::output_iterator_tag;

  explicit bond_insert_iterator(container_type& container) noexcept
  : container_{container}
  {
  }

  auto operator=(const bond& atom) -> bond_insert_iterator&
  {
    container_.add_bond(atom);
    return *this;
  }

  auto operator*() -> bond_insert_iterator&
  {
    return *this;
  }

  auto operator++() -> bond_insert_iterator&
  {
    return *this;
  }

  auto operator++(int) -> bond_insert_iterator&
  {
    return *this;
  }

private:
  container_type& container_;
};

} // namespace molphene

#endif
