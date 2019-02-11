#ifndef MOLPHENE_MOLECULE_ATOM_INSERT_ITERATOR_HPP
#define MOLPHENE_MOLECULE_ATOM_INSERT_ITERATOR_HPP

#include "atom.hpp"

namespace molphene {

template<typename TContainer>
struct atom_insert_iterator {
  using container_type = TContainer;

  using value_type = void;
  using difference_type = void;
  using pointer = void;
  using reference = void;
  using iterator_category = std::output_iterator_tag;

  explicit atom_insert_iterator(container_type& container) noexcept
  : container_{container}
  {
  }

  auto operator=(const atom& atom) -> atom_insert_iterator&
  {
    container_.add_atom(atom);
    return *this;
  }

  auto operator*() -> atom_insert_iterator&
  {
    return *this;
  }

  auto operator++() -> atom_insert_iterator&
  {
    return *this;
  }

  auto operator++(int) -> atom_insert_iterator&
  {
    return *this;
  }

private:
  container_type& container_;
};

} // namespace molphene

#endif
