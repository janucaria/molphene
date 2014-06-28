#ifndef __Molphene__Model__
#define __Molphene__Model__

#include <map>
#include <iterator>
#include "Chain.h"
#include "Atom.h"

namespace molphene {
    class Molecule;
    
    class Model {
    public:
        
        typedef std::map<unsigned int, Atom *> AtomMap;
        typedef std::map<char, Chain> ChainMap;
        
        class chain_iterator : public std::iterator<ChainMap::iterator::iterator_category, ChainMap::iterator, ChainMap::iterator::difference_type, Chain*, Chain&> {
            
        public:
            chain_iterator(value_type it);
            
            chain_iterator(const chain_iterator & cit);
            
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
        
        chain_iterator beginChain();
        
        chain_iterator endChain();
        
        ChainMap & getChains();
        
        void addAtom(Atom & atom);
        
        AtomMap & getAtoms();
        
        Molecule & getMolecule() const;
        
    private:
        Molecule * moleculePtr_;
        AtomMap atoms;
        ChainMap chains_;
    };
}

#endif /* defined(__Molphene__Model__) */
