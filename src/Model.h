#ifndef __Molphene__Model__
#define __Molphene__Model__

#include <map>
#include <iterator>
#include "Chain.h"
#include "Atom.h"
#include "Bond.h"

namespace molphene {
    class Molecule;
    
    class Model {
        typedef std::vector<Bond> BondList;
    public:
        
        typedef std::map<unsigned int, Atom*> AtomMap;
        typedef std::map<char, Chain> ChainMap;
        typedef BondList::iterator bond_iterator;
        
        class chain_iterator : public std::iterator<ChainMap::iterator::iterator_category, ChainMap::iterator, ChainMap::iterator::difference_type, Chain*, Chain&> {
            
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

        
        Model(Molecule & molecule);
        
        Chain & addChain(char chainID);
        
        Chain & getChain(char chainID);
        
        chain_iterator chainbegin();
        
        chain_iterator chainend();
        
        ChainMap & getChains();
        
        void addAtom(Atom & atom);
        
        Atom * getAtomBySerial(unsigned int serial);
        
        AtomMap & getAtoms();
        
        Molecule & getMolecule() const;
        
        void addBond(Atom & a1, Atom & a2);
        
        bond_iterator beginBond();
        
        bond_iterator endBond();
        
        
    private:
        Molecule * moleculePtr_;
        AtomMap atoms;
        ChainMap chains_;
        BondList bonds_;
    };
}

#endif /* defined(__Molphene__Model__) */
