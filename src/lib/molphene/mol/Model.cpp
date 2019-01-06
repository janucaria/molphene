#include "Model.hpp"
#include "Molecule.hpp"

namespace molphene {

Model::Model(Molecule& molecule)
: molecule_ptr_(&molecule)
{
}

void Model::add_atom(Atom& atom)
{
  atoms_.emplace(atom.serial(), &atom);
}

void Model::add_bond(Atom& a1, Atom& a2)
{
  bonds_.emplace_back(a1, a2);
}

auto Model::add_chain(char cid) -> Chain&
{
  std::pair<Chains::iterator, bool> emplaced =
   chains_.emplace(std::piecewise_construct,
                   std::make_tuple(cid),
                   std::forward_as_tuple(this, cid));
  return emplaced.first->second;
}

auto Model::chains() const -> const Chains&
{
  return chains_;
}

auto Model::chains_begin() -> ChainsIterator
{
  return Model::ChainsIterator(chains_.begin());
}

auto Model::chains_end() -> ChainsIterator
{
  return Model::ChainsIterator(chains_.end());
}

auto Model::get_atom(unsigned int serial) -> Atom*
{
  return atoms_.count(serial) ? atoms_.at(serial) : nullptr;
}

auto Model::get_chain(char cid) -> Chain*
{
  auto chainit = chains_.find(cid);
  if(chainit == chains_.end()) {
    return nullptr;
  }
  return &chainit->second;
}

auto Model::molecule() const -> Molecule&
{
  return *molecule_ptr_;
}

Model::ChainsIterable::ChainsIterable(Model& model)
: model_{model}
{
}

auto Model::ChainsIterable::begin() -> ChainsIterator
{
  return Model::ChainsIterator(model_.chains_.begin());
}

auto Model::ChainsIterable::end() -> ChainsIterator
{
  return Model::ChainsIterator(model_.chains_.end());
}

Model::BondsIterable::BondsIterable(Model& model)
: model_(model)
{
}

auto Model::BondsIterable::begin() -> BondsIterator
{
  return {model_.bonds_.begin()};
}

auto Model::BondsIterable::end() -> BondsIterator
{
  return {model_.bonds_.end()};
}

Model::ChainsIterator::ChainsIterator(Model::ChainsIterator::value_type it)
: it_(it)
{
}

auto Model::ChainsIterator::operator++() -> ChainsIterator&
{
  ++it_;
  return *this;
}

auto Model::ChainsIterator::operator++(int) -> const ChainsIterator
{
  Model::ChainsIterator tmp(*this);
  operator++();
  return tmp;
}

auto Model::ChainsIterator::operator==(const Model::ChainsIterator& rhs) -> bool
{
  return it_ == rhs.it_;
}

auto Model::ChainsIterator::operator!=(const Model::ChainsIterator& rhs) -> bool
{
  return it_ != rhs.it_;
}

auto Model::ChainsIterator::operator*() -> reference
{
  return it_->second;
}

auto Model::ChainsIterator::operator-> () -> pointer
{
  return &it_->second;
}
} // namespace molphene
