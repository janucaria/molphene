#ifndef __Molphene__Bond__
#define __Molphene__Bond__

#include "atom.h"

namespace molphene {
    class bond {
    public:
        bond(atom & a1, atom & a2);
        
        atom & getAtom1();
        atom & getAtom2();
        
    private:
        atom a1_;
        atom a2_;
    };
}

#endif /* defined(__Molphene__Bond__) */
