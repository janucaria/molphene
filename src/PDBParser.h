#ifndef __Molphene__PDBParser__
#define __Molphene__PDBParser__

#include <string>
#include <iostream>
#include <unordered_map>
#include <set>

#include "logger.h"
#include "Atom.h"
#include "Model.h"
#include "Molecule.h"
#include "Chain.h"
#include "Compound.h"
#include "Bond.h"

namespace molphene {
    class PDBParser {
    public:
        typedef std::pair<std::string, std::string> BondPair;
        typedef std::set<BondPair> BondPairList;
        typedef std::unordered_map<std::string, BondPairList> ResidueBondPairMap;
        
        PDBParser();
        
        void parse(Molecule & mol, std::istream & stream);
        
    private:
        const static ResidueBondPairMap resBondPairs;
        
        Model * currentModelPtr;
        Chain * currentChainPtr;
        Compound * currentCompoundPtr;
        
        std::string line_;
        
        inline std::string column(unsigned int start,  unsigned int end);
        
        float getReal(unsigned int start,  unsigned int end);
        
        unsigned int getInteger(unsigned int start,  unsigned int end);
        
        inline char getChar(unsigned int start);
        
        void handleATOMRecord(Molecule & mol);
        
        void handleMODELRecord(Molecule & mol);
        
        void handleCONECTRecord(Molecule & mol);
        
        void handleTERRecord(Molecule & mol);
        
        bool buildBond(Compound & comp1, std::string atomName1, Compound & comp2, std::string atomName2);
    };
}

#endif /* defined(__Molphene__PDBParser__) */
