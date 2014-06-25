#include "Compound.h"
#include "Chain.h"
#include "Model.h"

namespace molphene {
    Compound::Compound(Chain & chain, ResidueNumber resNum) :
    chainPtr_(&chain),
    resNum_(resNum)
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
    
    unsigned int Compound::getSequence() const {
        return std::get<0>(resNum_);
    }
    
    std::string Compound::getName() const {
        return std::get<1>(resNum_);
    }
    
    char Compound::getICode() const {
        return std::get<2>(resNum_);
    }
    
    Compound::ResidueNumber Compound::getResNum() {
        return resNum_;
    }
}