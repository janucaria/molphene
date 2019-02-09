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

auto Compound::add_atom(const std::string& element,
                        std::string name,
                        unsigned int serial) -> Atom&
{
  Atom& atm = atoms_.emplace(name, Atom(*this, element, name, serial))->second;
  chain().model().add_atom(atm);
  return atm;
}

auto Compound::atoms_begin(const std::string& name) -> AtomsIterator
{
  return Compound::AtomsIterator(atoms_.lower_bound(name));
}

auto Compound::atoms_end(const std::string& name) -> AtomsIterator
{
  return Compound::AtomsIterator(atoms_.upper_bound(name));
}

auto Compound::chain() const -> Chain&
{
  return *chain_ptr_;
}

auto Compound::icode() const -> char
{
  return std::get<2>(resnum_);
}

auto Compound::name() const -> std::string
{
  return std::get<1>(resnum_);
}

auto Compound::resnum() const -> ResidueNumber
{
  return resnum_;
}

auto Compound::sequence() const -> unsigned int
{
  return std::get<0>(resnum_);
}

Compound::AtomsIterator::AtomsIterator(Compound::AtomsIterator::value_type it)
: it_(it)
{
}

auto Compound::AtomsIterator::operator++() -> AtomsIterator&
{
  ++it_;
  return *this;
}

auto Compound::AtomsIterator::operator++(int) -> const AtomsIterator
{
  Compound::AtomsIterator tmp{*this};
  operator++();
  return tmp;
}

auto Compound::AtomsIterator::operator==(const Compound::AtomsIterator& rhs)
 -> bool
{
  return it_ == rhs.it_;
}

auto Compound::AtomsIterator::operator!=(const Compound::AtomsIterator& rhs)
 -> bool
{
  return it_ != rhs.it_;
}

auto Compound::AtomsIterator::operator*() -> reference
{
  return it_->second;
}

auto Compound::AtomsIterator::operator-> () -> pointer
{
  return &it_->second;
}

Compound::AtomsIterable::AtomsIterable(Compound& compound)
: compound_{compound}
{
}

auto Compound::AtomsIterable::begin() -> AtomsIterator
{
  return Compound::AtomsIterator(compound_.atoms_.begin());
}

auto Compound::AtomsIterable::end() -> AtomsIterator
{
  return Compound::AtomsIterator(compound_.atoms_.end());
}

} // namespace molphene
