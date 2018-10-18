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

Model::ChainsIterator
Model::chains_begin()
{
  return Model::ChainsIterator(chains_.begin());
}

Model::ChainsIterator
Model::chains_end()
{
  return Model::ChainsIterator(chains_.end());
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

Model::ChainsIterable::ChainsIterable(Model& model)
: model_ {model}
{
}

Model::ChainsIterator
Model::ChainsIterable::begin()
{
  return Model::ChainsIterator(model_.chains_.begin());
}

Model::ChainsIterator
Model::ChainsIterable::end()
{
  return Model::ChainsIterator(model_.chains_.end());
}

Model::BondsIterable::BondsIterable(Model& model)
: model_(model)
{
}

Model::BondsIterator
Model::BondsIterable::begin()
{
  return {model_.bonds_.begin()};
}

Model::BondsIterator
Model::BondsIterable::end()
{
  return {model_.bonds_.end()};
}

Model::ChainsIterator::ChainsIterator(Model::ChainsIterator::value_type it)
: it_(it)
{
}

Model::ChainsIterator&
Model::ChainsIterator::operator++()
{
  ++it_;
  return *this;
}

const Model::ChainsIterator
Model::ChainsIterator::operator++(int)
{
  Model::ChainsIterator tmp(*this);
  operator++();
  return tmp;
}

bool
Model::ChainsIterator::operator==(const Model::ChainsIterator& rhs)
{
  return it_ == rhs.it_;
}

bool
Model::ChainsIterator::operator!=(const Model::ChainsIterator& rhs)
{
  return it_ != rhs.it_;
}

Model::ChainsIterator::reference Model::ChainsIterator::operator*()
{
  return it_->second;
}

Model::ChainsIterator::pointer Model::ChainsIterator::operator->()
{
  return &it_->second;
}
} // namespace molphene
