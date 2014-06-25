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
        typedef std::tuple<unsigned int, std::string, unsigned int> ResidueNumber;
        typedef std::multimap<std::string, Atom> AtomMap;
        
        Compound(Chain & chain, ResidueNumber resNum);
        
        Atom & addAtom(std::string element, std::string name, unsigned int serial);
        
        Atom & getAtom(const std::string & name);
        
        const unsigned int & getSequence() const;
        
        const std::string & getName() const;
        
        const unsigned int & getICode() const;
        
        Chain & getChain() const;
        
    private:
        unsigned int sequence_;
        std::string name_;
        unsigned int iCode_;
        AtomMap atoms_;
        Chain * chainPtr_;
    };
}

#endif /* defined(__Molphene__Compound__) */
