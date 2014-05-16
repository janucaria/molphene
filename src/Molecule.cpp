#include "Molecule.h"

namespace molphene {
    Molecule::Molecule()
    {}
    
    void Molecule::addModel(Model & model) {
        models.push_back(std::move(model));
    }
    
    Molecule::ModelList & Molecule::getModels() {
        return models;
    }
}
