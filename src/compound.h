#ifndef __Molphene__Compound__
#define __Molphene__Compound__

#include "atom.h"
#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace molphene {
class chain;

class compound {
public:
  typedef std::multimap<std::string, atom> AtomMap;
  typedef std::tuple<unsigned int, std::string, char> ResidueNumber;

  class atom_iterator
  : public std::iterator<AtomMap::iterator::iterator_category,
                         AtomMap::iterator,
                         AtomMap::iterator::difference_type,
                         atom*,
                         atom&> {
  public:
    atom_iterator(value_type it);

    atom_iterator(const atom_iterator& cit);

    atom_iterator&
    operator++();

    atom_iterator
    operator++(int);

    bool
    operator==(const atom_iterator& rhs);

    bool
    operator!=(const atom_iterator& rhs);

    reference operator*();

    pointer operator->();

  private:
    value_type it_;
  };

  compound(chain& chain, unsigned int seqres, std::string resname, char icode);

  atom&
  addAtom(std::string element, std::string name, unsigned int serial);

  atom&
  getAtom(const std::string& name);

  AtomMap&
  getAtoms();

  atom_iterator
  atmbegin();

  atom_iterator
  atmend();

  atom_iterator
  atmbegin(const std::string& name);

  atom_iterator
  atmend(const std::string& name);

  unsigned int
  getSequence() const;

  std::string
  getName() const;

  char
  getICode() const;

  ResidueNumber
  getResNum();

  chain&
  getChain() const;

private:
  ResidueNumber resNum_;
  AtomMap atoms_;
  chain* chainPtr_;
};
} // namespace molphene

#endif
