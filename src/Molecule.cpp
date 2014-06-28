#include "Molecule.h"

namespace molphene {
    Molecule::Molecule()
    {}
    
    Model & Molecule::addModel() {
        models.emplace_back(*this);
        return models.at(models.size() - 1);
    }
    
    Molecule::ModelList & Molecule::getModels() {
        return models;
    }
    
    Molecule::model_iterator Molecule::beginModel() {
        return models.begin();
    }
    
    Molecule::model_iterator Molecule::endModel() {
        return models.end();
        
    }
}
