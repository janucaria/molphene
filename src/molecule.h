#ifndef __molphene__Molecule__
#define __molphene__Molecule__

#include <vector>
#include "model.h"

namespace molphene {
    class molecule {
    public:
        typedef std::vector<model> ModelList;
        typedef std::vector<model>::iterator model_iterator;
        
        molecule();
        
        model & addModel();
        
        model_iterator mdlbegin();
        
        model_iterator mdlend();
        
    private:
        ModelList models;
    };
}

#endif /* defined(__Molphene__Molecule__) */
