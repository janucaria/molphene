#include "PDBParser.h"

namespace molphene {
    PDBParser::PDBParser() {
        
    }
    
    void PDBParser::parse(Molecule & mol, const char * filePath) {
        std::ifstream fs;
        fs.open(filePath);
        if(fs.is_open()) {
            parse(mol, fs);
            fs.close();
        }
    }
    
    
    void PDBParser::parse(Molecule & mol, std::istream & stream) {
        
        Model * currentModelPtr = &mol.addModel();
        Chain * currentChainPtr = nullptr;
        Compound * currentCompoundPtr = nullptr;
        
        std::string recordName;
        
        std::string line;
        while(std::getline(stream, line)) {
            
            recordName = trim_right_copy(column(line, 1, 6));
            
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
            if(recordName.compare("ATOM") == 0 || recordName.compare("HETATM") == 0) {
                
                unsigned int aserial = static_cast<unsigned int>(std::stoul(column(line, 7, 11)));
                std::string aname = trim_copy(column(line, 13, 16));
                char aaltLoc = column(line, 17, 17).at(0);
                std::string aresName = trim_copy(column(line, 18, 20));
                char achainID = column(line, 22, 22).at(0);
                unsigned int aresSeq = static_cast<unsigned int>(std::stoul(column(line, 23, 26)));
                char aiCode = column(line, 27, 27).at(0);
                float ax = std::stof(column(line, 31, 38));
                float ay = std::stof(column(line, 39, 46));
                float az = std::stof(column(line, 47, 54));
                std::string aelement = trim_left_copy(column(line, 77, 78));
                
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
    
    inline std::string PDBParser::column(std::string & line, unsigned int start, unsigned int end) {
        return line.substr(start - 1, end - start + 1);
    }
    
}