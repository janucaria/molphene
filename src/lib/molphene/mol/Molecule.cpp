#include "Molecule.hpp"

namespace molphene {

Model&
Molecule::add_model()
{
  models_.emplace_back(*this);
  return models_.at(models_.size() - 1);
}

Molecule::ChainsIterator
Molecule::chains_begin()
{
  return Molecule::ChainsIterator(models_.begin());
}

Molecule::ChainsIterator
Molecule::chains_end()
{
  return Molecule::ChainsIterator(models_.end());
}

Molecule::ModelsIterator
Molecule::models_begin()
{
  return models_.begin();
}

Molecule::ModelsIterator
Molecule::models_end()
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

Molecule::ChainsIterator&
Molecule::ChainsIterator::operator++()
{
  ++cit_;
  if(cit_ == cet_) {
    ++it_;
    cit_ = it_->chains_begin();
    cet_ = it_->chains_end();
  }

  return *this;
}

const Molecule::ChainsIterator
Molecule::ChainsIterator::operator++(int)
{
  Molecule::ChainsIterator tmp(*this);
  operator++();
  return tmp;
}

bool
Molecule::ChainsIterator::operator==(const Molecule::ChainsIterator& rhs)
{
  return it_ == rhs.it_;
}

bool
Molecule::ChainsIterator::operator!=(const Molecule::ChainsIterator& rhs)
{
  return it_ != rhs.it_;
}

Molecule::ChainsIterator::reference Molecule::ChainsIterator::operator*()
{
  return cit_.operator*();
}

Molecule::ChainsIterator::pointer Molecule::ChainsIterator::operator->()
{
  return cit_.operator->();
}

Molecule::ModelsIterable::ModelsIterable(Molecule& molecule)
: molecule_{molecule}
{
}

Molecule::ModelsIterator
Molecule::ModelsIterable::begin()
{
  return {molecule_.models_.begin()};
}

Molecule::ModelsIterator
Molecule::ModelsIterable::end()
{
  return {molecule_.models_.end()};
}

} // namespace molphene
