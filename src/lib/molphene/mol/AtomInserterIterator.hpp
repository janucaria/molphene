#ifndef MOLPHENE_ATOM_INSERTER_ITERATOR_HPP
#define MOLPHENE_ATOM_INSERTER_ITERATOR_HPP

#include "../stdafx.hpp"

namespace molphene {

template<typename Container>
struct AtomInserterIterator {
  using container_type = Container;

  using value_type = void;
  using difference_type = void;
  using pointer = void;
  using reference = void;
  using iterator_category = std::output_iterator_tag;

  explicit AtomInserterIterator(container_type& container) noexcept
  : container_{container}
  {
  }

  auto operator=(const Atom& atom) -> AtomInserterIterator&
  {
    container_.add_atom(atom);
    return *this;
  }

  auto operator*() -> AtomInserterIterator&
  {
    return *this;
  }

  auto operator++() -> AtomInserterIterator&
  {
    return *this;
  }

  auto operator++(int) -> AtomInserterIterator&
  {
    return *this;
  }

private:
  container_type& container_;
};

} // namespace molphene

#endif
