#include "Compound.h"
#include "Chain.h"
#include "Model.h"

namespace molphene {
    Compound::Compound(Chain & chain, ResidueNumber resNum) :
    chainPtr_(&chain),
    sequence_(std::get<0>(resNum)),
    name_(std::get<1>(resNum)),
    iCode_(std::get<2>(resNum))
    {
        
    }
    
    Atom & Compound::addAtom(std::string element, std::string name, unsigned int serial) {
        Atom & atm = atoms_.emplace(name, Atom(*this, element, name, serial))->second;
        getChain().getModel().addAtom(atm);
        return atm;
    }
    
    Atom & Compound::getAtom(const std::string & name) {
        return atoms_.find(name)->second;
    }
    
    Chain & Compound::getChain() const {
        return *chainPtr_;
    }
    
    const unsigned int & Compound::getSequence() const {
        return sequence_;
    }
    
    const std::string & Compound::getName() const {
        return name_;
    }
    
    const unsigned int & Compound::getICode() const {
        return iCode_;
    }
}