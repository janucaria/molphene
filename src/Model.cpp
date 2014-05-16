#include "Model.h"

namespace molphene {
    Model::Model() {
        
    }
    
    void Model::addAtom(Atom atom) {
        atoms.insert(std::make_pair(atom.getSerial(), atom));
    }
    
    Model::AtomMap & Model::getAtoms() {
        return atoms;
    }
}