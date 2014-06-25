#ifndef __Molphene__Molecule__
#define __Molphene__Molecule__

#include <vector>
#include "Model.h"

namespace molphene {
    class Molecule {
    public:
        typedef std::vector<Model> ModelList;
        
        Molecule();
        
        Model & addModel();
        
        ModelList & getModels();
        
    private:
        ModelList models;
    };
}

#endif /* defined(__Molphene__Molecule__) */
