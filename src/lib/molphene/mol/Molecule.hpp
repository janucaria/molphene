#ifndef MOLPHENE_MOL_MOLECULE_HPP
#define MOLPHENE_MOL_MOLECULE_HPP

#include "Chain.hpp"
#include "Model.hpp"
#include <vector>

namespace molphene {
class Molecule {
  using Models = std::vector<Model>;

public:
  class ChainsIterator;

  class ModelsIterable;

  using ModelsIterator = Models::iterator;

  Model&
  add_model();

  ChainsIterator
  chains_begin();

  ChainsIterator
  chains_end();

  ModelsIterator
  models_begin();

  ModelsIterator
  models_end();

private:
  Models models_;
};

class Molecule::ChainsIterator
: public std::iterator<ModelsIterator::iterator_category,
                       ModelsIterator,
                       ModelsIterator::difference_type,
                       Chain*,
                       Chain&> {
public:
  explicit ChainsIterator(value_type it);

  ChainsIterator&
  operator++();

  const ChainsIterator
  operator++(int);

  bool
  operator==(const ChainsIterator& rhs);

  bool
  operator!=(const ChainsIterator& rhs);

  reference operator*();

  pointer operator->();

private:
  value_type it_;
  Model::ChainsIterator cit_;
  Model::ChainsIterator cet_;
};

class Molecule::ModelsIterable {
public:
  explicit ModelsIterable(Molecule& molecule);

  Molecule::ModelsIterator
  begin();

  Molecule::ModelsIterator
  end();

private:
  Molecule& molecule_;
};

} // namespace molphene

#endif
