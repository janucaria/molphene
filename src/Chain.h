#ifndef __Molphene__Chain__
#define __Molphene__Chain__

#include <map>
#include <vector>
#include "Compound.h"

namespace molphene {
    class Model;
    
    class Chain {
    public:
        typedef std::map<Compound::ResidueNumber, Compound> CompoundMap;
        
        Chain(Model & model, unsigned char chainId);
        
        Compound & addCompound(const Compound::ResidueNumber & resNum);
        
        Compound & getCompound(const Compound::ResidueNumber & resNum);
        
        Model & getModel() const;
        
    private:
        unsigned char chainID_;
        
        CompoundMap compounds_;
        
        CompoundMap ligands_;
        
        Model * modelPtr_;
    };
}

#endif /* defined(__Molphene__Chain__) */
