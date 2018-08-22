#ifndef MOLPHENE_MOL_COMPOUND_HPP
#define MOLPHENE_MOL_COMPOUND_HPP

#include "Atom.hpp"
#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace molphene {
class Chain;

class Compound {
public:
  class Atoms_iterator;

  class Atoms_iterable;

  using Atoms_container = std::multimap<std::string, Atom>;

  using Residue_number = std::tuple<unsigned int, std::string, char>;

  Compound(Chain& chain, unsigned int seqres, std::string resname, char icode);

  Atom&
  add_atom(const std::string& element, std::string name, unsigned int serial);

  Atoms_iterator
  atoms_begin(const std::string& name);

  Atoms_iterator
  atoms_end(const std::string& name);

  Chain&
  chain() const;

  char
  icode() const;

  std::string
  name() const;

  Residue_number
  resnum() const;

  unsigned int
  sequence() const;

private:
  Atoms_container atoms_;

  Chain* chain_ptr_;

  Residue_number resnum_;
};

class Compound::Atoms_iterator
: public std::iterator<Atoms_container::iterator::iterator_category,
                       Atoms_container::iterator,
                       Atoms_container::iterator::difference_type,
                       Atom*,
                       Atom&> {
public:
  explicit Atoms_iterator(value_type it);

  Atoms_iterator&
  operator++();

  const Atoms_iterator
  operator++(int);

  bool
  operator==(const Atoms_iterator& rhs);

  bool
  operator!=(const Atoms_iterator& rhs);

  reference operator*();

  pointer operator->();

private:
  value_type it_;
};

class Compound::Atoms_iterable {
public:
  explicit Atoms_iterable(Compound& compound);

  Compound::Atoms_iterator
  begin();

  Compound::Atoms_iterator
  end();

private:
  Compound& compound_;
};
} // namespace molphene

#endif
