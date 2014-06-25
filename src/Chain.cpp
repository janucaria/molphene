#include "Chain.h"
#include "Model.h"

namespace molphene {
    Chain::Chain(Model & model, unsigned char chainID) :
    modelPtr_(&model),
    chainID_(chainID)
    {
        
    }
    
    Compound & Chain::addCompound(const Compound::ResidueNumber & resNum) {
        std::pair<CompoundMap::iterator, bool> emplaced = compounds_.emplace(resNum, Compound(*this, resNum));
        return emplaced.first->second;
    }
    
    Compound & Chain::getCompound(const Compound::ResidueNumber & resNum) {
        return compounds_.at(resNum);
    }
    
    Model & Chain::getModel() const {
        return *modelPtr_;
    }
}
