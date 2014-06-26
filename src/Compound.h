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
        
        Compound(Chain & chain, ResidueNumber resNum);
        
        Atom & addAtom(std::string element, std::string name, unsigned int serial);
        
        Atom & getAtom(const std::string & name);
        
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
