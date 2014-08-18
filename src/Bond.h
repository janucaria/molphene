#ifndef __Molphene__Bond__
#define __Molphene__Bond__

#include "Atom.h"

namespace molphene {
    class Bond {
    public:
        Bond(Atom & a1, Atom & a2);
    private:
        Atom a1_;
        Atom a2_;
    };
}

#endif /* defined(__Molphene__Bond__) */
