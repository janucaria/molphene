#ifndef __Molphene__PDBParser__
#define __Molphene__PDBParser__

#include <string>
#include <fstream>
#include <tuple>

#include "utils.h"
#include "logger.h"
#include "Atom.h"
#include "Model.h"
#include "Molecule.h"
#include "Chain.h"
#include "Compound.h"

namespace molphene {
    class PDBParser {
    public:
        PDBParser();
        
        void parse(Molecule & mol, const char * filePath);
        
        void parse(Molecule & mol, std::istream & stream);
        
        static inline std::string column(std::string & line, unsigned int start,  unsigned int end);
                
    };
}

#endif /* defined(__Molphene__PDBParser__) */
