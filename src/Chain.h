#ifndef __Molphene__Chain__
#define __Molphene__Chain__

#include <map>
#include <vector>
#include "Compound.h"

namespace molphene {
    class Model;
    
    class Chain {
    public:
        typedef std::vector<Compound> CompoundList;
        typedef CompoundList::iterator compound_iterator;
                
        Chain(Model & model, char chainId);
        
        Compound & addCompound(const Compound::ResidueNumber & resNum);
        
        Compound & getCompound(const Compound::ResidueNumber & resNum);
        
        compound_iterator beginCompound();
        
        compound_iterator endCompound();
        
        compound_iterator endResidue();
        
        Model & getModel() const;
        
        char getId() const;
        
        void terminate();
        
    private:
        typedef std::map<Compound::ResidueNumber, CompoundList::size_type> CompoundMap;
        
        char chainID_;
        
        CompoundList::size_type ter_;
        
        CompoundList compounds_;
        
        CompoundMap res_lookup_;
        
        Model * modelPtr_;
    };
}

#endif /* defined(__Molphene__Chain__) */
