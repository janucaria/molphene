#ifndef __Molphene__Compound__
#define __Molphene__Compound__

#include <tuple>
#include <string>
#include <map>
#include <vector>
#include "Atom.h"

namespace molphene {
    class Chain;
    
    class Compound {
    public:
        typedef std::tuple<unsigned int, std::string, char> ResidueNumber;
        typedef std::multimap<std::string, Atom> AtomMap;
        
        
        class atom_iterator : public std::iterator<AtomMap::iterator::iterator_category, AtomMap::iterator, AtomMap::iterator::difference_type, Atom*, Atom&> {
            
        public:
            atom_iterator(value_type it);
            
            atom_iterator(const atom_iterator & cit);
            
            atom_iterator& operator++();
            
            atom_iterator operator++(int);
            
            bool operator==(const atom_iterator& rhs);
            
            bool operator!=(const atom_iterator& rhs);
            
            reference operator*();
            
            pointer operator->();
            
        private:
            value_type it_;
        };

        
        Compound(Chain & chain, ResidueNumber resNum);
        
        Atom & addAtom(std::string element, std::string name, unsigned int serial);
        
        Atom & getAtom(const std::string & name);
        
        AtomMap & getAtoms();
        
        atom_iterator atmbegin();
        
        atom_iterator atmend();
        
        atom_iterator atmbegin(const std::string & name);
        
        atom_iterator atmend(const std::string & name);
        
        unsigned int getSequence() const;
        
        std::string getName() const;
        
        char getICode() const;
        
        ResidueNumber getResNum();
        
        Chain & getChain() const;
        
    private:
        ResidueNumber resNum_;
        AtomMap atoms_;
        Chain * chainPtr_;
    };
}

#endif /* defined(__Molphene__Compound__) */
