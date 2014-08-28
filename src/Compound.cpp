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
    
    Compound::AtomMap & Compound::getAtoms() {
        return atoms_;
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
    
    Compound::atom_iterator Compound::atmbegin() {
        return atoms_.begin();
    }
    
    Compound::atom_iterator Compound::atmend() {
        return atoms_.end();
    }
    
    Compound::atom_iterator Compound::atmbegin(const std::string & name) {
        return atoms_.lower_bound(name);
    }
    
    Compound::atom_iterator Compound::atmend(const std::string & name) {
        return atoms_.upper_bound(name);
    }
    
    Compound::atom_iterator::atom_iterator(Compound::atom_iterator::value_type it) : it_(it) {
    }
    
    Compound::atom_iterator::atom_iterator(const Compound::atom_iterator & cit) : it_(cit.it_) {
        
    }
    
    Compound::atom_iterator & Compound::atom_iterator::operator++() {
        ++it_;
        return *this;
    }
    
    Compound::atom_iterator Compound::atom_iterator::operator++(int) {
        Compound::atom_iterator tmp(*this);
        operator++();
        return tmp;
    }
    
    bool Compound::atom_iterator::operator==(const Compound::atom_iterator& rhs) {
        return it_ == rhs.it_;
    }
    
    bool Compound::atom_iterator::operator!=(const Compound::atom_iterator& rhs) {
        return it_ != rhs.it_;
    }
    
    Compound::atom_iterator::reference Compound::atom_iterator::operator*() {
        return it_->second;
    }
    
    Compound::atom_iterator::pointer Compound::atom_iterator::operator->() {
        return &it_->second;
    }
    
}