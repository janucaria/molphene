#ifndef __Molphene__model__
#define __Molphene__model__

#include <map>
#include <iterator>
#include "chain.h"
#include "atom.h"
#include "bond.h"

namespace molphene {
    class molecule;
    
    class model {
        typedef std::vector<bond> BondList;
    public:
        
        typedef std::map<unsigned int, atom*> AtomMap;
        typedef std::map<char, chain> ChainMap;
        typedef BondList::iterator bond_iterator;
        
        class chain_iterator : public std::iterator<ChainMap::iterator::iterator_category, ChainMap::iterator, ChainMap::iterator::difference_type, chain*, chain&> {
            
        public:
            chain_iterator(value_type it);
            
            chain_iterator& operator++();
            
            chain_iterator operator++(int);
            
            bool operator==(const chain_iterator& rhs);
            
            bool operator!=(const chain_iterator& rhs);
            
            reference operator*();
            
            pointer operator->();
            
        private:
            value_type it_;
        };

        
        model(molecule & molecule);
        
        chain & addChain(char chainID);
        
        chain & getChain(char chainID);
        
        chain_iterator chainbegin();
        
        chain_iterator chainend();
        
        void addAtom(atom & atom);
        
        atom * getAtomBySerial(unsigned int serial);
        
        molecule & getMolecule() const;
        
        void addBond(atom & a1, atom & a2);
        
        bond_iterator beginBond();
        
        bond_iterator endBond();
        
        
    private:
        molecule * moleculePtr_;
        AtomMap atoms;
        ChainMap chains_;
        BondList bonds_;
    };
}

#endif /* defined(__Molphene__model__) */
