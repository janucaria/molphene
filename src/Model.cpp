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
    
    Molecule & Model::getMolecule() const {
        return *moleculePtr_;
    }
}