#ifndef MOLPHENE_MOLECULE_COMPOUND_HPP
#define MOLPHENE_MOLECULE_COMPOUND_HPP

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

  auto add_atom(const std::string& element,
                std::string name,
                unsigned int serial) -> Atom&;

  auto atoms_begin(const std::string& name) -> AtomsIterator;

  auto atoms_end(const std::string& name) -> AtomsIterator;

  auto chain() const -> Chain&;

  auto icode() const -> char;

  auto name() const -> std::string;

  auto resnum() const -> ResidueNumber;

  auto sequence() const -> unsigned int;

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

  auto operator++() -> AtomsIterator&;

  auto operator++(int) -> const AtomsIterator;

  auto operator==(const AtomsIterator& rhs) -> bool;

  auto operator!=(const AtomsIterator& rhs) -> bool;

  auto operator*() -> reference;

  auto operator-> () -> pointer;

private:
  value_type it_;
};

class Compound::AtomsIterable {
public:
  explicit AtomsIterable(Compound& compound);

  auto begin() -> AtomsIterator;

  auto end() -> AtomsIterator;

private:
  Compound& compound_;
};
} // namespace molphene

#endif
