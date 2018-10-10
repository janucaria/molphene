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
  class AtomsIterator;

  class AtomsIterable;

  using AtomsContainer = std::multimap<std::string, Atom>;

  using ResidueNumber = std::tuple<unsigned int, std::string, char>;

  Compound(Chain& chain, unsigned int seqres, std::string resname, char icode);

  Atom&
  add_atom(const std::string& element, std::string name, unsigned int serial);

  AtomsIterator
  atoms_begin(const std::string& name);

  AtomsIterator
  atoms_end(const std::string& name);

  Chain&
  chain() const;

  char
  icode() const;

  std::string
  name() const;

  ResidueNumber
  resnum() const;

  unsigned int
  sequence() const;

private:
  AtomsContainer atoms_;

  Chain* chain_ptr_;

  ResidueNumber resnum_;
};

class Compound::AtomsIterator
: public std::iterator<AtomsContainer::iterator::iterator_category,
                       AtomsContainer::iterator,
                       AtomsContainer::iterator::difference_type,
                       Atom*,
                       Atom&> {
public:
  explicit AtomsIterator(value_type it);

  AtomsIterator&
  operator++();

  const AtomsIterator
  operator++(int);

  bool
  operator==(const AtomsIterator& rhs);

  bool
  operator!=(const AtomsIterator& rhs);

  reference operator*();

  pointer operator->();

private:
  value_type it_;
};

class Compound::AtomsIterable {
public:
  explicit AtomsIterable(Compound& compound);

  Compound::AtomsIterator
  begin();

  Compound::AtomsIterator
  end();

private:
  Compound& compound_;
};
} // namespace molphene

#endif
