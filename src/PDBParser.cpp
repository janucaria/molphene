#include "PDBParser.h"

namespace molphene {
    PDBParser::PDBParser() {
        
    }
    
    void PDBParser::parse(Molecule & mol, std::istream & stream) {
        Model * currentModelPtr = nullptr;
        Chain * currentChainPtr = nullptr;
        Compound * currentCompoundPtr = nullptr;
        
        std::string recordName;
        
        while(std::getline(stream, line_)) {
            
            recordName = boost::trim_right_copy(column(1, 6));
            
            if(recordName.compare("MODEL") == 0) {
                currentModelPtr = &mol.addModel();
                currentChainPtr = nullptr;
                
            } else if(recordName.compare("ATOM") == 0 || recordName.compare("HETATM") == 0) {
                
                //    COLUMNS        DATA  TYPE    FIELD        DEFINITION
                //    -------------------------------------------------------------------------------------
                //    1 -  6        Record name   "ATOM  "
                //    7 - 11        Integer       serial       Atom  serial number.
                //    13 - 16        Atom          name         Atom name.
                //    17             Character     altLoc       Alternate location indicator.
                //    18 - 20        Residue name  resName      Residue name.
                //    22             Character     chainID      Chain identifier.
                //    23 - 26        Integer       resSeq       Residue sequence number.
                //    27             AChar         iCode        Code for insertion of residues.
                //    31 - 38        Real(8.3)     x            Orthogonal coordinates for X in Angstroms.
                //    39 - 46        Real(8.3)     y            Orthogonal coordinates for Y in Angstroms.
                //    47 - 54        Real(8.3)     z            Orthogonal coordinates for Z in Angstroms.
                //    55 - 60        Real(6.2)     occupancy    Occupancy.
                //    61 - 66        Real(6.2)     tempFactor   Temperature  factor.
                //    77 - 78        LString(2)    element      Element symbol, right-justified.
                //    79 - 80        LString(2)    charge       Charge  on the atom.
                
                unsigned int aserial = getInteger(7, 11);
                std::string aname = boost::trim_copy(column(13, 16));
                char aaltLoc = getChar(17);
                std::string aresName = boost::trim_copy(column(18, 20));
                char achainID = getChar(22);
                unsigned int aresSeq = getInteger(23, 26);
                char aiCode = column(27, 27).at(0);
                float ax = getReal(31, 38);
                float ay = getReal(39, 46);
                float az = getReal(47, 54);
                std::string aelement = boost::trim_left_copy(column(77, 78));
                
                if(!currentModelPtr) {
                    currentModelPtr = &mol.addModel();
                    currentChainPtr = nullptr;
                }
                
                if(!currentChainPtr || currentChainPtr->getId() != achainID) {
                    try {
                        currentChainPtr = &currentModelPtr->getChain(achainID);
                    } catch (const std::out_of_range & oor) {
                        currentChainPtr = &currentModelPtr->addChain(achainID);
                    }
                    
                    currentCompoundPtr = nullptr;
                }
                
                Compound::ResidueNumber resNum = std::make_tuple(aresSeq, aresName, aiCode);
                
                if(!currentCompoundPtr || currentCompoundPtr->getResNum() != resNum) {
                    try {
                        currentCompoundPtr = &currentChainPtr->getCompound(resNum);
                    } catch (const std::out_of_range & oor) {
                        currentCompoundPtr = &currentChainPtr->addCompound(resNum);
                    }
                }
                
                Atom & atom = currentCompoundPtr->addAtom(aelement, aname, aserial);
                atom.setPosition(ax, ay, az);
                atom.setAltLoc(aaltLoc);
                
            }
        }
    }
    
    std::string PDBParser::column(unsigned int start, unsigned int end) {
        return line_.substr(start - 1, end - start + 1);
    }
    
    float PDBParser::getReal(unsigned int start,  unsigned int end) {
        return std::stof(column(start, end));
    }
    
    unsigned int PDBParser::getInteger(unsigned int start,  unsigned int end) {
        try {
            return static_cast<unsigned int>(std::stoul(column(start, end)));
        } catch (const std::invalid_argument & ia) {
            return 0;
        }
    }
    
    char PDBParser::getChar(unsigned int start) {
        return column(start, start).at(0);
    }
    
}