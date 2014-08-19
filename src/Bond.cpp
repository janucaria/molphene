#include "Bond.h"

namespace molphene {
    Bond::Bond(Atom & a1, Atom & a2) : a1_(a1), a2_(a2) {
        
    }
    
    Atom & Bond::getAtom1() {
        return a1_;
    }
    
    Atom & Bond::getAtom2() {
        return a2_;
    }

}