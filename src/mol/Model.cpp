#include "Model.hpp"
#include "Molecule.hpp"

namespace molphene {

Model::Model(Molecule& molecule)
: molecule_ptr_(&molecule)
{
}

void
Model::add_atom(Atom& atom)
{
  atoms_.emplace(atom.serial(), &atom);
}

void
Model::add_bond(Atom& a1, Atom& a2)
{
  bonds_.emplace_back(a1, a2);
}

Chain&
Model::add_chain(char cid)
{
  std::pair<Chains::iterator, bool> emplaced =
   chains_.emplace(std::piecewise_construct,
                   std::make_tuple(cid),
                   std::forward_as_tuple(this, cid));
  return emplaced.first->second;
}

const Model::Chains&
Model::chains() const
{
  return chains_;
}

Model::Chains_iterator
Model::chains_begin()
{
  return Model::Chains_iterator(chains_.begin());
}

Model::Chains_iterator
Model::chains_end()
{
  return Model::Chains_iterator(chains_.end());
}

Atom*
Model::get_atom(unsigned int serial)
{
  return atoms_.count(serial) ? atoms_.at(serial) : nullptr;
}

Chain*
Model::get_chain(char cid)
{
  auto chainit = chains_.find(cid);
  if(chainit == chains_.end()) {
    return nullptr;
  }
  return &chainit->second;
}

Molecule&
Model::molecule() const
{
  return *molecule_ptr_;
}

Model::Chains_iterable::Chains_iterable(Model& model)
: model_{model}
{
}

Model::Chains_iterator
Model::Chains_iterable::begin()
{
  return Model::Chains_iterator(model_.chains_.begin());
}

Model::Chains_iterator
Model::Chains_iterable::end()
{
  return Model::Chains_iterator(model_.chains_.end());
}

Model::Bonds_iterable::Bonds_iterable(Model& model)
: model_(model)
{
}

Model::Bonds_iterator
Model::Bonds_iterable::begin()
{
  return {model_.bonds_.begin()};
}

Model::Bonds_iterator
Model::Bonds_iterable::end()
{
  return {model_.bonds_.end()};
}

Model::Chains_iterator::Chains_iterator(Model::Chains_iterator::value_type it)
: it_(it)
{
}

Model::Chains_iterator&
Model::Chains_iterator::operator++()
{
  ++it_;
  return *this;
}

const Model::Chains_iterator
Model::Chains_iterator::operator++(int)
{
  Model::Chains_iterator tmp(*this);
  operator++();
  return tmp;
}

bool
Model::Chains_iterator::operator==(const Model::Chains_iterator& rhs)
{
  return it_ == rhs.it_;
}

bool
Model::Chains_iterator::operator!=(const Model::Chains_iterator& rhs)
{
  return it_ != rhs.it_;
}

Model::Chains_iterator::reference Model::Chains_iterator::operator*()
{
  return it_->second;
}

Model::Chains_iterator::pointer Model::Chains_iterator::operator->()
{
  return &it_->second;
}
} // namespace molphene
