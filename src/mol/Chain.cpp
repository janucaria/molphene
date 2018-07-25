#include "Chain.hpp"
#include "Model.hpp"

namespace molphene {

Chain::Chain(Model* model, char chainId)
: chain_id_(chainId)
, model_ptr_(model)
{
}

Compound&
Chain::add_compound(const Compound::Residue_number& resnum)
{
  compounds_.emplace_back(
   *this, std::get<0>(resnum), std::get<1>(resnum), std::get<2>(resnum));

  std::pair<Compound_map::iterator, bool> emplaced =
   res_lookup_.emplace(std::piecewise_construct,
                       std::make_tuple(resnum),
                       std::forward_as_tuple(compounds_.size() - 1));
  return compounds_.at(emplaced.first->second);
}

Compound*
Chain::get_compound(const Compound::Residue_number& resnum)
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
  return get_compound(Compound::Residue_number(reseq, resname, icode));
}

const Chain::Compounds_type&
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

Chain::Residue_iterator::Residue_iterator(Chain& chain)
: chain_{chain}
{
}

Chain::Compounds_iterator
Chain::Residue_iterator::begin()
{
  return chain_.compounds_.begin();
}

Chain::Compounds_iterator
Chain::Residue_iterator::end()
{
  auto it = begin();
  std::advance(it, chain_.ter_);
  return it;
}

Chain::Compound_iterator::Compound_iterator(Chain& chain)
: chain_{chain}
{
}

Chain::Compounds_iterator
Chain::Compound_iterator::begin()
{
  return chain_.compounds_.begin();
}

Chain::Compounds_iterator
Chain::Compound_iterator::end()
{
  return chain_.compounds_.end();
}

Chain::Ligan_iterator::Ligan_iterator(Chain& chain)
: chain_{chain}
{
}

Chain::Compounds_iterator
Chain::Ligan_iterator::begin()
{
  auto it = std::begin(chain_.compounds_);
  std::advance(it, chain_.ter_);
  return it;
}

Chain::Compounds_iterator
Chain::Ligan_iterator::end()
{
  return chain_.compounds_.end();
}

} // namespace molphene
