#ifndef MOLPHENE_MOLECULE_ATOM_INSERT_ITERATOR_HPP
#define MOLPHENE_MOLECULE_ATOM_INSERT_ITERATOR_HPP

#include "stdafx.hpp"

namespace molphene {

template<typename Container>
struct AtomInsertIterator {
  using container_type = Container;

  using value_type = void;
  using difference_type = void;
  using pointer = void;
  using reference = void;
  using iterator_category = std::output_iterator_tag;

  explicit AtomInsertIterator(container_type& container) noexcept
  : container_{container}
  {
  }

  auto operator=(const Atom& atom) -> AtomInsertIterator&
  {
    container_.add_atom(atom);
    return *this;
  }

  auto operator*() -> AtomInsertIterator&
  {
    return *this;
  }

  auto operator++() -> AtomInsertIterator&
  {
    return *this;
  }

  auto operator++(int) -> AtomInsertIterator&
  {
    return *this;
  }

private:
  container_type& container_;
};

} // namespace molphene

#endif
