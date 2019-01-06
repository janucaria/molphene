#include "Molecule.hpp"

namespace molphene {

auto Molecule::add_model() -> Model&
{
  models_.emplace_back(*this);
  return models_.at(models_.size() - 1);
}

auto Molecule::chains_begin() -> ChainsIterator
{
  return Molecule::ChainsIterator(models_.begin());
}

auto Molecule::chains_end() -> ChainsIterator
{
  return Molecule::ChainsIterator(models_.end());
}

auto Molecule::models_begin() -> ModelsIterator
{
  return models_.begin();
}

auto Molecule::models_end() -> ModelsIterator
{
  return models_.end();
}

Molecule::ChainsIterator::ChainsIterator(
 Molecule::ChainsIterator::value_type it)
: it_(it)
, cit_(it_->chains_begin())
, cet_(it_->chains_end())
{
}

auto Molecule::ChainsIterator::operator++() -> ChainsIterator&
{
  ++cit_;
  if(cit_ == cet_) {
    ++it_;
    cit_ = it_->chains_begin();
    cet_ = it_->chains_end();
  }

  return *this;
}

auto Molecule::ChainsIterator::operator++(int) -> const ChainsIterator
{
  Molecule::ChainsIterator tmp(*this);
  operator++();
  return tmp;
}

auto Molecule::ChainsIterator::operator==(const Molecule::ChainsIterator& rhs)
 -> bool
{
  return it_ == rhs.it_;
}

auto Molecule::ChainsIterator::operator!=(const Molecule::ChainsIterator& rhs)
 -> bool
{
  return it_ != rhs.it_;
}

auto Molecule::ChainsIterator::operator*() -> reference
{
  return cit_.operator*();
}

auto Molecule::ChainsIterator::operator-> () -> pointer
{
  return cit_.operator->();
}

Molecule::ModelsIterable::ModelsIterable(Molecule& molecule)
: molecule_{molecule}
{
}

auto Molecule::ModelsIterable::begin() -> ModelsIterator
{
  return {molecule_.models_.begin()};
}

auto Molecule::ModelsIterable::end() -> ModelsIterator
{
  return {molecule_.models_.end()};
}

} // namespace molphene
