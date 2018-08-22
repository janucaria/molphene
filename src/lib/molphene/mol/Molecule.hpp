#ifndef MOLPHENE_MOL_MOLECULE_HPP
#define MOLPHENE_MOL_MOLECULE_HPP

#include "Chain.hpp"
#include "Model.hpp"
#include <vector>

namespace molphene {
class Molecule {
  using Models = std::vector<Model>;

public:
  class Chains_iterator;

  class Models_iterable;

  using Models_iterator = Models::iterator;

  Model&
  add_model();

  Chains_iterator
  chains_begin();

  Chains_iterator
  chains_end();

  Models_iterator
  models_begin();

  Models_iterator
  models_end();

private:
  Models models_;
};

class Molecule::Chains_iterator
: public std::iterator<Models_iterator::iterator_category,
                       Models_iterator,
                       Models_iterator::difference_type,
                       Chain*,
                       Chain&> {
public:
  explicit Chains_iterator(value_type it);

  Chains_iterator&
  operator++();

  const Chains_iterator
  operator++(int);

  bool
  operator==(const Chains_iterator& rhs);

  bool
  operator!=(const Chains_iterator& rhs);

  reference operator*();

  pointer operator->();

private:
  value_type it_;
  Model::Chains_iterator cit_;
  Model::Chains_iterator cet_;
};

class Molecule::Models_iterable {
public:
  explicit Models_iterable(Molecule& molecule);

  Molecule::Models_iterator
  begin();

  Molecule::Models_iterator
  end();

private:
  Molecule& molecule_;
};

} // namespace molphene

#endif
