#ifndef __Molphene__Molecule__
#define __Molphene__Molecule__

#include <vector>
#include "Model.h"

namespace molphene {
    class Molecule {
    public:
        typedef std::vector<Model> ModelList;
        typedef std::vector<Model>::iterator model_iterator;
        
        Molecule();
        
        Model & addModel();
        
        ModelList & getModels();
        
        model_iterator mdlbegin();
        
        model_iterator mdlend();
        
    private:
        ModelList models;
    };
}

#endif /* defined(__Molphene__Molecule__) */
