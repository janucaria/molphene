#include "Chain.hpp"
#include "Model.hpp"

namespace molphene {

Chain::Chain(Model* model, char chainId)
: chain_id_(chainId)
, model_ptr_(model)
{
}

auto Chain::add_compound(const Compound::ResidueNumber& resnum) -> Compound&
{
  compounds_.emplace_back(
   *this, std::get<0>(resnum), std::get<1>(resnum), std::get<2>(resnum));

  std::pair<CompoundMap::iterator, bool> emplaced =
   res_lookup_.emplace(std::piecewise_construct,
                       std::make_tuple(resnum),
                       std::forward_as_tuple(compounds_.size() - 1));
  return compounds_.at(emplaced.first->second);
}

auto Chain::get_compound(const Compound::ResidueNumber& resnum) -> Compound*
{
  auto comptypeit = res_lookup_.find(resnum);
  if(comptypeit == res_lookup_.end()) {
    return nullptr;
  }
  auto compn = comptypeit->second;

  return compn < compounds_.size() ? &compounds_.at(compn) : nullptr;
}

auto Chain::get_compound(unsigned int reseq, std::string resname, char icode)
 -> Compound*
{
  return get_compound(Compound::ResidueNumber(reseq, resname, icode));
}

auto Chain::compounds() const noexcept -> const Compounds&
{
  return compounds_;
}

auto Chain::id() const -> char
{
  return chain_id_;
}

auto Chain::model() const -> Model&
{
  return *model_ptr_;
}

void Chain::terminate()
{
  ter_ = compounds_.size();
}

Chain::ResidueIterator::ResidueIterator(Chain& chain)
: chain_{chain}
{
}

auto Chain::ResidueIterator::begin() -> CompoundsIterator
{
  return chain_.compounds_.begin();
}

auto Chain::ResidueIterator::end() -> CompoundsIterator
{
  auto it = begin();
  std::advance(it, chain_.ter_);
  return it;
}

Chain::CompoundIterator::CompoundIterator(Chain& chain)
: chain_{chain}
{
}

auto Chain::CompoundIterator::begin() -> CompoundsIterator
{
  return chain_.compounds_.begin();
}

auto Chain::CompoundIterator::end() -> CompoundsIterator
{
  return chain_.compounds_.end();
}

Chain::LiganIterator::LiganIterator(Chain& chain)
: chain_{chain}
{
}

auto Chain::LiganIterator::begin() -> CompoundsIterator
{
  auto it = std::begin(chain_.compounds_);
  std::advance(it, chain_.ter_);
  return it;
}

auto Chain::LiganIterator::end() -> CompoundsIterator
{
  return chain_.compounds_.end();
}

} // namespace molphene
