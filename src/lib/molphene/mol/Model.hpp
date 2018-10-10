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

  void
  add_atom(Atom& atom);

  void
  add_bond(Atom& a1, Atom& a2);

  const Chains&
  chains() const;

  Chain&
  add_chain(char cid);

  ChainsIterator
  chains_begin();

  ChainsIterator
  chains_end();

  Atom*
  get_atom(unsigned int serial);

  Chain*
  get_chain(char cid);

  Molecule&
  molecule() const;

private:
  Atoms atoms_;

  Bonds bonds_;

  Chains chains_;

  Molecule* molecule_ptr_;
};

class Model::ChainsIterable {
public:
  explicit ChainsIterable(Model& model);

  Model::ChainsIterator
  begin();

  Model::ChainsIterator
  end();

private:
  Model& model_;
};

class Model::BondsIterable {
public:
  explicit BondsIterable(Model& model);

  Model::BondsIterator
  begin();

  Model::BondsIterator
  end();

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
};

} // namespace molphene

#endif
