#ifndef MOLPHENE_MOL_MODEL_HPP
#define MOLPHENE_MOL_MODEL_HPP

#include "Atom.hpp"
#include "Bond.hpp"
#include "Chain.hpp"
#include <iterator>
#include <map>

namespace molphene {
class Molecule;

class Model {
  using Bonds = std::vector<Bond>;

  using Chains = std::map<char, Chain>;

  using Atoms = std::map<unsigned int, Atom*>;

public:
  class ChainsIterable;

  class BondsIterable;

  class ChainsIterator;

  using BondsIterator = Bonds::iterator;

  explicit Model(Molecule& molecule);

  void add_atom(Atom& atom);

  void add_bond(Atom& a1, Atom& a2);

  auto chains() const -> const Chains&;

  auto add_chain(char cid) -> Chain&;

  auto chains_begin() -> ChainsIterator;

  auto chains_end() -> ChainsIterator;

  auto get_atom(unsigned int serial) -> Atom*;

  auto get_chain(char cid) -> Chain*;

  auto molecule() const -> Molecule&;

private:
  Atoms atoms_;

  Bonds bonds_;

  Chains chains_;

  Molecule* molecule_ptr_;
};

class Model::ChainsIterable {
public:
  explicit ChainsIterable(Model& model);

  auto begin() -> Model::ChainsIterator;

  auto end() -> ChainsIterator;

private:
  Model& model_;
};

class Model::BondsIterable {
public:
  explicit BondsIterable(Model& model);

  auto begin() -> BondsIterator;

  auto end() -> BondsIterator;

private:
  Model model_;
};

class Model::ChainsIterator
: public std::iterator<Chains::iterator::iterator_category,
                       Chains::iterator,
                       Chains::iterator::difference_type,
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
};

} // namespace molphene

#endif
