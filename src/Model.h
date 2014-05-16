#ifndef __Molphene__Model__
#define __Molphene__Model__

#include <map>
#include "Atom.h"

namespace molphene {
    class Model {
    public:
        typedef std::map<unsigned int, Atom> AtomMap;
        
        Model();
        
        void addAtom(Atom atom);
        
        AtomMap & getAtoms();
        
    private:
        AtomMap atoms;
    };
}

#endif /* defined(__Molphene__Model__) */
