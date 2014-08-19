#include "Model.h"
#include "Molecule.h"

namespace molphene {
    Model::Model(Molecule & mol) :
    moleculePtr_(&mol)
    {
        
    }
    
    void Model::addAtom(Atom & atom) {
        atoms.emplace(atom.getSerial(), &atom);
    }
    
    Model::AtomMap & Model::getAtoms() {
        return atoms;
    }
    
    Chain & Model::addChain(char chainID) {
        std::pair<ChainMap::iterator, bool> emplaced = chains_.emplace(std::piecewise_construct, std::make_tuple(chainID), std::forward_as_tuple(*this, chainID));
        return emplaced.first->second;
    }
    
    Chain & Model::getChain(char chainID) {
        return chains_.at(chainID);
    }
    
    Model::ChainMap & Model::getChains() {
        return chains_;
    }
    
    Atom * Model::getAtomBySerial(unsigned int serial) {
        return atoms.at(serial);
    }
    
    Molecule & Model::getMolecule() const {
        return *moleculePtr_;
    }
    
    void Model::addBond(Atom & a1, Atom & a2) {
        bonds_.emplace_back(a1, a2);
    }
    
    
    Model::BondList::iterator Model::beginBond() {
        return bonds_.begin();
    }
    
    Model::BondList::iterator Model::endBond() {
        return bonds_.end();
    }
    
    
    
    Model::chain_iterator Model::beginChain() {
        return chains_.begin();
    }
    
    Model::chain_iterator Model::endChain() {
        return chains_.end();
    }
    
    Model::chain_iterator::chain_iterator(Model::chain_iterator::value_type it) : it_(it) {
    }
    
    Model::chain_iterator::chain_iterator(const Model::chain_iterator & cit) : it_(cit.it_) {
        
    }
    
    Model::chain_iterator & Model::chain_iterator::operator++() {
         ++it_;
        return *this;
    }
    
    Model::chain_iterator Model::chain_iterator::operator++(int) {
        Model::chain_iterator tmp(*this);
        operator++();
        return tmp;
    }
    
    bool Model::chain_iterator::operator==(const Model::chain_iterator& rhs) {
        return it_ == rhs.it_;
    }
    
    bool Model::chain_iterator::operator!=(const Model::chain_iterator& rhs) {
        return it_ != rhs.it_;
    }
    
    Model::chain_iterator::reference Model::chain_iterator::operator*() {
        return it_->second;
    }
    
    Model::chain_iterator::pointer Model::chain_iterator::operator->() {
        return &it_->second;
    }
    
}