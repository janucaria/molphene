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
  class Chains_iterable;

  class Bonds_iterable;

  class Chains_iterator;

  using Bonds_iterator = Bonds::iterator;

  explicit Model(Molecule& molecule);

  void
  add_atom(Atom& atom);

  void
  add_bond(Atom& a1, Atom& a2);

  const Chains&
  chains() const;

  Chain&
  add_chain(char cid);

  Chains_iterator
  chains_begin();

  Chains_iterator
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

class Model::Chains_iterable {
public:
  explicit Chains_iterable(Model& model);

  Model::Chains_iterator
  begin();

  Model::Chains_iterator
  end();

private:
  Model& model_;
};

class Model::Bonds_iterable {
public:
  explicit Bonds_iterable(Model& model);

  Model::Bonds_iterator
  begin();

  Model::Bonds_iterator
  end();

private:
  Model model_;
};

class Model::Chains_iterator
: public std::iterator<Chains::iterator::iterator_category,
                       Chains::iterator,
                       Chains::iterator::difference_type,
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
};

} // namespace molphene

#endif
