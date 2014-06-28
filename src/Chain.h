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
        
        class compound_iterator : public std::iterator<CompoundMap::iterator::iterator_category, CompoundMap::iterator, CompoundMap::iterator::difference_type, Compound*, Compound&> {
            
        public:
            compound_iterator(value_type it);
            
            compound_iterator(const compound_iterator & cit);
            
            compound_iterator& operator++();
            
            compound_iterator operator++(int);
            
            bool operator==(const compound_iterator& rhs);
            
            bool operator!=(const compound_iterator& rhs);
            
            reference operator*();
            
            pointer operator->();
            
        private:
            value_type it_;
        };
        
        Chain(Model & model, char chainId);
        
        Compound & addCompound(const Compound::ResidueNumber & resNum);
        
        Compound & getCompound(const Compound::ResidueNumber & resNum);
        
        CompoundMap & getCompounds();
        
        compound_iterator beginCompound();
        
        compound_iterator endCompound();
        
        Model & getModel() const;
        
        char getId() const;
        
    private:
        char chainID_;
        
        CompoundMap compounds_;
        
        CompoundMap ligands_;
        
        Model * modelPtr_;
    };
}

#endif /* defined(__Molphene__Chain__) */
