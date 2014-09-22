#include "compound.h"
#include "chain.h"
#include "model.h"

namespace molphene {
    compound::compound(chain & chain, unsigned int seqres, std::string resname, char icode) :
    chainPtr_(&chain),
    resNum_(seqres, resname, icode)
    {
    }

    atom & compound::addAtom(std::string element, std::string name, unsigned int serial) {
        atom & atm = atoms_.emplace(name, atom(*this, element, name, serial))->second;
        getChain().getModel().addAtom(atm);
        return atm;
    }

    atom & compound::getAtom(const std::string & name) {
        return atoms_.find(name)->second;
    }

    compound::AtomMap & compound::getAtoms() {
        return atoms_;
    }

    chain & compound::getChain() const {
        return *chainPtr_;
    }

    unsigned int compound::getSequence() const {
        return std::get<0>(resNum_);
    }

    std::string compound::getName() const {
        return std::get<1>(resNum_);
    }

    char compound::getICode() const {
        return std::get<2>(resNum_);
    }

    compound::ResidueNumber compound::getResNum() {
        return resNum_;
    }

    compound::atom_iterator compound::atmbegin() {
        return atoms_.begin();
    }

    compound::atom_iterator compound::atmend() {
        return atoms_.end();
    }

    compound::atom_iterator compound::atmbegin(const std::string & name) {
        return atoms_.lower_bound(name);
    }

    compound::atom_iterator compound::atmend(const std::string & name) {
        return atoms_.upper_bound(name);
    }

    compound::atom_iterator::atom_iterator(compound::atom_iterator::value_type it) : it_(it) {
    }

    compound::atom_iterator::atom_iterator(const compound::atom_iterator & cit) : it_(cit.it_) {

    }

    compound::atom_iterator & compound::atom_iterator::operator++() {
        ++it_;
        return *this;
    }

    compound::atom_iterator compound::atom_iterator::operator++(int) {
        compound::atom_iterator tmp(*this);
        operator++();
        return tmp;
    }

    bool compound::atom_iterator::operator==(const compound::atom_iterator& rhs) {
        return it_ == rhs.it_;
    }

    bool compound::atom_iterator::operator!=(const compound::atom_iterator& rhs) {
        return it_ != rhs.it_;
    }

    compound::atom_iterator::reference compound::atom_iterator::operator*() {
        return it_->second;
    }

    compound::atom_iterator::pointer compound::atom_iterator::operator->() {
        return &it_->second;
    }
    
}