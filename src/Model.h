#ifndef __Molphene__Model__
#define __Molphene__Model__

#include <map>
#include "Chain.h"
#include "Atom.h"

namespace molphene {
    class Molecule;
    
    class Model {
    public:
        typedef std::map<unsigned int, Atom *> AtomMap;
        typedef std::map<char, Chain> ChainMap;
        
        Model(Molecule & molecule);
        
        Chain & addChain(char chainID);
        
        Chain & getChain(char chainID);
        
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
