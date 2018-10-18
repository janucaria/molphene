#include "Compound.hpp"
#include "Chain.hpp"
#include "Model.hpp"

namespace molphene {

Compound::Compound(Chain& chain,
                   unsigned int seqres,
                   std::string resname,
                   char icode)
: chain_ptr_(&chain)
, resnum_(seqres, resname, icode)
{
}

Atom&
Compound::add_atom(const std::string& element,
                   std::string name,
                   unsigned int serial)
{
  Atom& atm = atoms_.emplace(name, Atom(*this, element, name, serial))->second;
  chain().model().add_atom(atm);
  return atm;
}

Compound::AtomsIterator
Compound::atoms_begin(const std::string& name)
{
  return Compound::AtomsIterator(atoms_.lower_bound(name));
}

Compound::AtomsIterator
Compound::atoms_end(const std::string& name)
{
  return Compound::AtomsIterator(atoms_.upper_bound(name));
}

Chain&
Compound::chain() const
{
  return *chain_ptr_;
}

char
Compound::icode() const
{
  return std::get<2>(resnum_);
}

std::string
Compound::name() const
{
  return std::get<1>(resnum_);
}

Compound::ResidueNumber
Compound::resnum() const
{
  return resnum_;
}

unsigned int
Compound::sequence() const
{
  return std::get<0>(resnum_);
}

Compound::AtomsIterator::AtomsIterator(Compound::AtomsIterator::value_type it)
: it_(it)
{
}

Compound::AtomsIterator&
Compound::AtomsIterator::operator++()
{
  ++it_;
  return *this;
}

const Compound::AtomsIterator
Compound::AtomsIterator::operator++(int)
{
  Compound::AtomsIterator tmp {*this};
  operator++();
  return tmp;
}

bool
Compound::AtomsIterator::operator==(const Compound::AtomsIterator& rhs)
{
  return it_ == rhs.it_;
}

bool
Compound::AtomsIterator::operator!=(const Compound::AtomsIterator& rhs)
{
  return it_ != rhs.it_;
}

Compound::AtomsIterator::reference Compound::AtomsIterator::operator*()
{
  return it_->second;
}

Compound::AtomsIterator::pointer Compound::AtomsIterator::operator->()
{
  return &it_->second;
}

Compound::AtomsIterable::AtomsIterable(Compound& compound)
: compound_ {compound}
{
}

Compound::AtomsIterator
Compound::AtomsIterable::begin()
{
  return Compound::AtomsIterator(compound_.atoms_.begin());
}

Compound::AtomsIterator
Compound::AtomsIterable::end()
{
  return Compound::AtomsIterator(compound_.atoms_.end());
}

} // namespace molphene
