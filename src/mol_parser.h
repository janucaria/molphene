#ifndef __molphene__mol_parser__
#define __molphene__mol_parser__

#include <string>
#include <iostream>
#include <unordered_map>
#include <set>

#include "atom.h"
#include "model.h"
#include "molecule.h"
#include "chain.h"
#include "compound.h"
#include "bond.h"

namespace molphene {
    class mol_parser {
    public:
        mol_parser();
        void parse(molecule & mol, std::istream & stream);
        
    private:
        std::string line_;
        
        void read_atoms_record(unsigned int serial);
        
        void read_bonds_record(molecule & mol);
        
        std::string column(int start, int end);
        
        float get_real(int start, int end);
        
        int get_int(int start, int end);
        
        compound * current_compound;
        
    };
}


#endif
