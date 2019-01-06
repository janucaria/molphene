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

  auto add_model() -> Model&;

  auto chains_begin() -> ChainsIterator;

  auto chains_end() -> ChainsIterator;

  auto models_begin() -> ModelsIterator;

  auto models_end() -> ModelsIterator;

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

  auto operator++() -> ChainsIterator&;

  auto operator++(int) -> const ChainsIterator;

  auto operator==(const ChainsIterator& rhs) -> bool;

  auto operator!=(const ChainsIterator& rhs) -> bool;

  auto operator*() -> reference;

  auto operator-> () -> pointer;

private:
  value_type it_;
  Model::ChainsIterator cit_;
  Model::ChainsIterator cet_;
};

class Molecule::ModelsIterable {
public:
  explicit ModelsIterable(Molecule& molecule);

  auto begin() -> ModelsIterator;

  auto end() -> ModelsIterator;

private:
  Molecule& molecule_;
};

} // namespace molphene

#endif
