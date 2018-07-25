#include "model.h"
#include "molecule.h"

namespace molphene {
model::model(molecule& mol)
: moleculePtr_(&mol)
{
}

void
model::addAtom(atom& atom)
{
  atoms.emplace(atom.getSerial(), &atom);
}

chain&
model::addChain(char chainID)
{
  std::pair<ChainMap::iterator, bool> emplaced =
   chains_.emplace(std::piecewise_construct,
                   std::make_tuple(chainID),
                   std::forward_as_tuple(*this, chainID));
  return emplaced.first->second;
}

chain&
model::getChain(char chainID)
{
  return chains_.at(chainID);
}

atom*
model::getAtomBySerial(unsigned int serial)
{
  return atoms.at(serial);
}

molecule&
model::getMolecule() const
{
  return *moleculePtr_;
}

void
model::addBond(atom& a1, atom& a2)
{
  bonds_.emplace_back(a1, a2);
}

model::BondList::iterator
model::beginBond()
{
  return bonds_.begin();
}

model::BondList::iterator
model::endBond()
{
  return bonds_.end();
}

model::chain_iterator
model::chainbegin()
{
  return chains_.begin();
}

model::chain_iterator
model::chainend()
{
  return chains_.end();
}

model::chain_iterator::chain_iterator(model::chain_iterator::value_type it)
: it_(it)
{
}

model::chain_iterator&
model::chain_iterator::operator++()
{
  ++it_;
  return *this;
}

model::chain_iterator
model::chain_iterator::operator++(int)
{
  model::chain_iterator tmp(*this);
  operator++();
  return tmp;
}

bool
model::chain_iterator::operator==(const model::chain_iterator& rhs)
{
  return it_ == rhs.it_;
}

bool
model::chain_iterator::operator!=(const model::chain_iterator& rhs)
{
  return it_ != rhs.it_;
}

model::chain_iterator::reference model::chain_iterator::operator*()
{
  return it_->second;
}

model::chain_iterator::pointer model::chain_iterator::operator->()
{
  return &it_->second;
}

} // namespace molphene