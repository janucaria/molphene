#ifndef __Molphene__Chain__
#define __Molphene__Chain__

#include <map>
#include <vector>
#include "compound.h"

namespace molphene {
    class model;
    
    class chain {
    public:
        typedef std::vector<compound> CompoundList;
        typedef CompoundList::iterator compound_iterator;
                
        chain(model & model, char chainId);
        
        compound & addCompound(const compound::ResidueNumber & resNum);
        
        compound & getCompound(const compound::ResidueNumber & resNum);
        
        compound_iterator compbegin();
        
        compound_iterator compend();
        
        compound_iterator resend();
        
        model & getModel() const;
        
        char getId() const;
        
        void terminate();
        
    private:
        typedef std::map<compound::ResidueNumber, CompoundList::size_type> CompoundMap;
        
        char chainID_;
        
        CompoundList::size_type ter_;
        
        CompoundList compounds_;
        
        CompoundMap res_lookup_;
        
        model * modelPtr_;
    };
}

#endif /* defined(__Molphene__Chain__) */
