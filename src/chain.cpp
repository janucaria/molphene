#include "chain.h"
#include "model.h"

namespace molphene {
chain::chain(model& model, char chainID)
: modelPtr_(&model)
, chainID_(chainID)
, ter_(0)
{
}

compound&
chain::addCompound(const compound::ResidueNumber& resNum)
{
  compounds_.emplace_back(
   *this, std::get<0>(resNum), std::get<1>(resNum), std::get<2>(resNum));
  std::pair<CompoundMap::iterator, bool> emplaced =
   res_lookup_.emplace(std::piecewise_construct,
                       std::make_tuple(resNum),
                       std::forward_as_tuple(compounds_.size() - 1));
  return compounds_.at(emplaced.first->second);
}

compound&
chain::getCompound(const compound::ResidueNumber& resNum)
{
  return compounds_.at(res_lookup_.at(resNum));
}

chain::compound_iterator
chain::compbegin()
{
  return compounds_.begin();
}

chain::compound_iterator
chain::compend()
{
  return compounds_.end();
}

chain::compound_iterator
chain::resend()
{
  chain::compound_iterator it = compounds_.begin();
  std::advance(it, ter_);
  return it;
}

model&
chain::getModel() const
{
  return *modelPtr_;
}

char
chain::getId() const
{
  return chainID_;
}

void
chain::terminate()
{
  ter_ = compounds_.size();
}
} // namespace molphene
