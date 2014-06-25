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
    
    Chain & Model::addChain(const unsigned char & chainID) {
        std::pair<ChainMap::iterator, bool> emplaced = chains_.emplace(chainID, Chain(*this, chainID));
        return emplaced.first->second;
    }
    
    Chain & Model::getChain(const unsigned char & chainID) {
        return chains_.at(chainID);
    }
    
    Molecule & Model::getMolecule() const {
        return *moleculePtr_;
    }
}