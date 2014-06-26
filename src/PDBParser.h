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
        
    private:
        std::string line_;
        
        inline std::string column(unsigned int start,  unsigned int end);
        
        float getReal(unsigned int start,  unsigned int end);
        
        unsigned int getInteger(unsigned int start,  unsigned int end);
        
        inline char getChar(unsigned int start);
    };
}

#endif /* defined(__Molphene__PDBParser__) */
