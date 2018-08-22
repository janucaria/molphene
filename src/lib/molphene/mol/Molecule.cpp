#include "Molecule.hpp"

namespace molphene {

Model&
Molecule::add_model()
{
  models_.emplace_back(*this);
  return models_.at(models_.size() - 1);
}

Molecule::Chains_iterator
Molecule::chains_begin()
{
  return Molecule::Chains_iterator(models_.begin());
}

Molecule::Chains_iterator
Molecule::chains_end()
{
  return Molecule::Chains_iterator(models_.end());
}

Molecule::Models_iterator
Molecule::models_begin()
{
  return models_.begin();
}

Molecule::Models_iterator
Molecule::models_end()
{
  return models_.end();
}

Molecule::Chains_iterator::Chains_iterator(
 Molecule::Chains_iterator::value_type it)
: it_(it)
, cit_(it_->chains_begin())
, cet_(it_->chains_end())
{
}

Molecule::Chains_iterator&
Molecule::Chains_iterator::operator++()
{
  ++cit_;
  if(cit_ == cet_) {
    ++it_;
    cit_ = it_->chains_begin();
    cet_ = it_->chains_end();
  }

  return *this;
}

const Molecule::Chains_iterator
Molecule::Chains_iterator::operator++(int)
{
  Molecule::Chains_iterator tmp(*this);
  operator++();
  return tmp;
}

bool
Molecule::Chains_iterator::operator==(const Molecule::Chains_iterator& rhs)
{
  return it_ == rhs.it_;
}

bool
Molecule::Chains_iterator::operator!=(const Molecule::Chains_iterator& rhs)
{
  return it_ != rhs.it_;
}

Molecule::Chains_iterator::reference Molecule::Chains_iterator::operator*()
{
  return cit_.operator*();
}

Molecule::Chains_iterator::pointer Molecule::Chains_iterator::operator->()
{
  return cit_.operator->();
}

Molecule::Models_iterable::Models_iterable(Molecule& molecule)
: molecule_{molecule}
{
}

Molecule::Models_iterator
Molecule::Models_iterable::begin()
{
  return {molecule_.models_.begin()};
}

Molecule::Models_iterator
Molecule::Models_iterable::end()
{
  return {molecule_.models_.end()};
}

} // namespace molphene
