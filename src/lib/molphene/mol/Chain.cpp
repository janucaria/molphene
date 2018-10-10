#include "Chain.hpp"
#include "Model.hpp"

namespace molphene {

Chain::Chain(Model* model, char chainId)
: chain_id_(chainId)
, model_ptr_(model)
{
}

Compound&
Chain::add_compound(const Compound::ResidueNumber& resnum)
{
  compounds_.emplace_back(
   *this, std::get<0>(resnum), std::get<1>(resnum), std::get<2>(resnum));

  std::pair<CompoundMap::iterator, bool> emplaced =
   res_lookup_.emplace(std::piecewise_construct,
                       std::make_tuple(resnum),
                       std::forward_as_tuple(compounds_.size() - 1));
  return compounds_.at(emplaced.first->second);
}

Compound*
Chain::get_compound(const Compound::ResidueNumber& resnum)
{
  auto comptypeit = res_lookup_.find(resnum);
  if(comptypeit == res_lookup_.end()) {
    return nullptr;
  }
  auto compn = comptypeit->second;

  return compn < compounds_.size() ? &compounds_.at(compn) : nullptr;
}

Compound*
Chain::get_compound(unsigned int reseq, std::string resname, char icode)
{
  return get_compound(Compound::ResidueNumber(reseq, resname, icode));
}

const Chain::Compounds&
Chain::compounds() const noexcept
{
  return compounds_;
}

char
Chain::id() const
{
  return chain_id_;
}

Model&
Chain::model() const
{
  return *model_ptr_;
}

void
Chain::terminate()
{
  ter_ = compounds_.size();
}

Chain::ResidueIterator::ResidueIterator(Chain& chain)
: chain_{chain}
{
}

Chain::CompoundsIterator
Chain::ResidueIterator::begin()
{
  return chain_.compounds_.begin();
}

Chain::CompoundsIterator
Chain::ResidueIterator::end()
{
  auto it = begin();
  std::advance(it, chain_.ter_);
  return it;
}

Chain::CompoundIterator::CompoundIterator(Chain& chain)
: chain_{chain}
{
}

Chain::CompoundsIterator
Chain::CompoundIterator::begin()
{
  return chain_.compounds_.begin();
}

Chain::CompoundsIterator
Chain::CompoundIterator::end()
{
  return chain_.compounds_.end();
}

Chain::LiganIterator::LiganIterator(Chain& chain)
: chain_{chain}
{
}

Chain::CompoundsIterator
Chain::LiganIterator::begin()
{
  auto it = std::begin(chain_.compounds_);
  std::advance(it, chain_.ter_);
  return it;
}

Chain::CompoundsIterator
Chain::LiganIterator::end()
{
  return chain_.compounds_.end();
}

} // namespace molphene
