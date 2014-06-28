#include "Chain.h"
#include "Model.h"

namespace molphene {
    Chain::Chain(Model & model, char chainID) :
    modelPtr_(&model),
    chainID_(chainID)
    {
        
    }
    
    Compound & Chain::addCompound(const Compound::ResidueNumber & resNum) {
        std::pair<CompoundMap::iterator, bool> emplaced = compounds_.emplace(std::piecewise_construct, std::make_tuple(resNum), std::forward_as_tuple(*this, resNum));
        return emplaced.first->second;
    }
    
    Compound & Chain::getCompound(const Compound::ResidueNumber & resNum) {
        return compounds_.at(resNum);
    }
    
    Chain::CompoundMap & Chain::getCompounds() {
        return compounds_;
    }
    
    Chain::compound_iterator Chain::beginCompound() {
        return compounds_.begin();
    }
    
    Chain::compound_iterator Chain::endCompound() {
        return compounds_.end();
    }
    
    Model & Chain::getModel() const {
        return *modelPtr_;
    }
    
    char Chain::getId() const {
        return chainID_;
    }
    
    
    Chain::compound_iterator::compound_iterator(Chain::compound_iterator::value_type it) : it_(it) {
    }
    
    Chain::compound_iterator::compound_iterator(const Chain::compound_iterator & cit) : it_(cit.it_) {
        
    }
    
    Chain::compound_iterator & Chain::compound_iterator::operator++() {
        ++it_;
        return *this;
    }
    
    Chain::compound_iterator Chain::compound_iterator::operator++(int) {
        Chain::compound_iterator tmp(*this);
        operator++();
        return tmp;
    }
    
    bool Chain::compound_iterator::operator==(const Chain::compound_iterator& rhs) {
        return it_ == rhs.it_;
    }
    
    bool Chain::compound_iterator::operator!=(const Chain::compound_iterator& rhs) {
        return it_ != rhs.it_;
    }
    
    Chain::compound_iterator::reference Chain::compound_iterator::operator*() {
        return it_->second;
    }
    
    Chain::compound_iterator::pointer Chain::compound_iterator::operator->() {
        return &it_->second;
    }
}
