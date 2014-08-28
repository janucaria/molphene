#include "Chain.h"
#include "Model.h"

namespace molphene {
    Chain::Chain(Model & model, char chainID)
    : modelPtr_(&model)
    , chainID_(chainID)
    , ter_(0)
    {
    }
    
    Compound & Chain::addCompound(const Compound::ResidueNumber & resNum) {
        compounds_.emplace_back(*this, resNum);
        std::pair<CompoundMap::iterator, bool> emplaced = res_lookup_.emplace(std::piecewise_construct, std::make_tuple(resNum), std::forward_as_tuple(compounds_.size() - 1));
        return compounds_.at(emplaced.first->second);
    }
    
    Compound & Chain::getCompound(const Compound::ResidueNumber & resNum) {
        return compounds_.at(res_lookup_.at(resNum));
    }
    
    Chain::compound_iterator Chain::compbegin() {
        return compounds_.begin();
    }
    
    Chain::compound_iterator Chain::compend() {
        return compounds_.end();
    }
    
    Chain::compound_iterator Chain::resend() {
        Chain::compound_iterator it = compounds_.begin();
        std::advance(it, ter_);
        return it;
    }
    
    Model & Chain::getModel() const {
        return *modelPtr_;
    }
    
    char Chain::getId() const {
        return chainID_;
    }
    
    void Chain::terminate() {
        ter_ = compounds_.size();
    }
}
