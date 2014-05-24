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
        
        Model model;
        
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
                
                unsigned int aserial = static_cast<unsigned int>(std::stoul(line.substr(7, 11)));
                float ax = std::stof(column(line, 31, 38));
                float ay = std::stof(column(line, 39, 46));
                float az = std::stof(column(line, 47, 54));
                
                std::string aelement = trim_left_copy(column(line, 77, 78));
                
                Atom atom(aelement, aserial);
                atom.setPosition(ax, ay, az);
                
                model.addAtom(atom);
            }
            
        }
        
        mol.addModel(model);
    }
    
    inline std::string PDBParser::column(std::string & line, unsigned int start, unsigned int end) {
        return line.substr(start - 1, end - start + 1);
    }
    
}