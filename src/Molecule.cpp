#include "Molecule.h"

namespace molphene {
    Molecule::Molecule()
    {}
    
    Model & Molecule::addModel() {
        models.emplace_back(*this);
        return *models.end();
    }
    
    Molecule::ModelList & Molecule::getModels() {
        return models;
    }
}
