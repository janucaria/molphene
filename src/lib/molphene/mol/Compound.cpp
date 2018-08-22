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

Compound::Atoms_iterator
Compound::atoms_begin(const std::string& name)
{
  return Compound::Atoms_iterator(atoms_.lower_bound(name));
}

Compound::Atoms_iterator
Compound::atoms_end(const std::string& name)
{
  return Compound::Atoms_iterator(atoms_.upper_bound(name));
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

Compound::Residue_number
Compound::resnum() const
{
  return resnum_;
}

unsigned int
Compound::sequence() const
{
  return std::get<0>(resnum_);
}

Compound::Atoms_iterator::Atoms_iterator(
 Compound::Atoms_iterator::value_type it)
: it_(it)
{
}

Compound::Atoms_iterator&
Compound::Atoms_iterator::operator++()
{
  ++it_;
  return *this;
}

const Compound::Atoms_iterator
Compound::Atoms_iterator::operator++(int)
{
  Compound::Atoms_iterator tmp{*this};
  operator++();
  return tmp;
}

bool
Compound::Atoms_iterator::operator==(const Compound::Atoms_iterator& rhs)
{
  return it_ == rhs.it_;
}

bool
Compound::Atoms_iterator::operator!=(const Compound::Atoms_iterator& rhs)
{
  return it_ != rhs.it_;
}

Compound::Atoms_iterator::reference Compound::Atoms_iterator::operator*()
{
  return it_->second;
}

Compound::Atoms_iterator::pointer Compound::Atoms_iterator::operator->()
{
  return &it_->second;
}

Compound::Atoms_iterable::Atoms_iterable(Compound& compound)
: compound_{compound}
{
}

Compound::Atoms_iterator
Compound::Atoms_iterable::begin()
{
  return Compound::Atoms_iterator(compound_.atoms_.begin());
}

Compound::Atoms_iterator
Compound::Atoms_iterable::end()
{
  return Compound::Atoms_iterator(compound_.atoms_.end());
}

} // namespace molphene
