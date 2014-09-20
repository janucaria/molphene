#include <cstdlib>
#include "PDBParser.h"

#include <boost/algorithm/string/trim.hpp>

namespace molphene {
    PDBParser::PDBParser() {
        
    }
    
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
    void PDBParser::handleATOMRecord(molecule & mol) {
        
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
        
        compound::ResidueNumber resNum(aresSeq, aresName, aiCode);
        
        if(!currentCompoundPtr || currentCompoundPtr->getResNum() != resNum) {
            try {
                currentCompoundPtr = &currentChainPtr->getCompound(resNum);
            } catch (const std::out_of_range & oor) {
                currentCompoundPtr = &currentChainPtr->addCompound(resNum);
            }
        }
        
        atom & atom = currentCompoundPtr->addAtom(aelement, aname, aserial);
        atom.setPosition(ax, ay, az);
        atom.setAltLoc(aaltLoc);
    }
    
    //    COLUMNS        DATA  TYPE    FIELD          DEFINITION
    //    ---------------------------------------------------------------------------------------
    //    1 -  6        Record name   "MODEL "
    //    11 - 14        Integer       serial         Model serial number.
    void PDBParser::handleMODELRecord(molecule & mol) {
        currentModelPtr = &mol.addModel();
        currentChainPtr = nullptr;
    }
    
    //    COLUMNS       DATA  TYPE      FIELD        DEFINITION
    //    -------------------------------------------------------------------------
    //    1 -  6        Record name    "CONECT"
    //    7 - 11       Integer        serial       Atom  serial number
    //    12 - 16        Integer        serial       Serial number of bonded atom
    //    17 - 21        Integer        serial       Serial  number of bonded atom
    //    22 - 26        Integer        serial       Serial number of bonded atom
    //    27 - 31        Integer        serial       Serial number of bonded atom
    void PDBParser::handleCONECTRecord(molecule & mol) {
        unsigned int atomSerial1 = getInteger(7, 11);
        
        molecule::model_iterator modelIt = mol.mdlbegin();
        molecule::model_iterator modelEndIt = mol.mdlend();
        
        for( ; modelIt != modelEndIt; ++modelIt) {
            atom * atm1 = modelIt->getAtomBySerial(atomSerial1);
            
            for(unsigned int i = 12; i <= 27; i += 5) {
                unsigned int atomSerial2 = getInteger(i, i + 4);
                if(!atomSerial2) {
                    break;
                }
                if(atomSerial1 < atomSerial2) {
                    atom * atm2 = modelIt->getAtomBySerial(atomSerial2);
                    modelIt->addBond(*atm1, *atm2);
                }
            }
        }
    }
    
    //    COLUMNS        DATA  TYPE    FIELD           DEFINITION
    //    -------------------------------------------------------------------------
    //    1 -  6        Record name   "TER   "
    //    7 - 11        Integer       serial          Serial number.
    //    18 - 20        Residue name  resName         Residue name.
    //    22             Character     chainID         Chain identifier.
    //    23 - 26        Integer       resSeq          Residue sequence number.
    //    27             AChar         iCode           Insertion code.
    void PDBParser::handleTERRecord(molecule & mol) {
        chain::compound_iterator compoundIt = currentChainPtr->compbegin();
        chain::compound_iterator compoundEndIt = currentChainPtr->compend();
        
        compound * prevResiduePtr = nullptr;
        
        for( ; compoundIt != compoundEndIt; ++compoundIt) {
            compound & compnd = *compoundIt;
            std::string resName = compnd.getName();
            PDBParser::ResidueBondPairMap::const_iterator bpairsIt = resBondPairs.find(resName);
            
            if(bpairsIt != resBondPairs.cend()) {
                PDBParser::BondPairList bpairs = bpairsIt->second;
                PDBParser::BondPairList::iterator bpairIt = bpairs.begin();
                PDBParser::BondPairList::iterator bpairEndIt = bpairs.end();
                
                for( ; bpairIt != bpairEndIt; ++bpairIt) {
                    buildBond(compnd, bpairIt->first, compnd, bpairIt->second);
                }
            }
            
            if(prevResiduePtr) {
                if(!buildBond(*prevResiduePtr, "C", compnd, "N")) {
                    buildBond(*prevResiduePtr, "O3'", compnd, "P");
                }
            }
            
            prevResiduePtr = &compnd;
        }
        
        currentChainPtr->terminate();
    }
    
    bool PDBParser::buildBond(compound & comp1, std::string atomName1, compound & comp2, std::string atomName2) {
        compound::atom_iterator atom1It = comp1.atmbegin(atomName1);
        compound::atom_iterator atom1EndIt = comp1.atmend(atomName1);
        
        if(atom1It == atom1EndIt) {
            return false;
        }
        
        do {
            char altloc1 = atom1It->getAltLoc();
            compound::atom_iterator atom2It = comp2.atmbegin(atomName2);
            compound::atom_iterator atom2EndIt = comp2.atmend(atomName2);
            
            for ( ; atom2It != atom2EndIt; ++atom2It) {
                if(altloc1) {
                    char altloc2 = atom2It->getAltLoc();
                    if(altloc1 == altloc2) {
                        currentModelPtr->addBond(*atom1It, *atom2It);
                        break;
                    }
                } else {
                    currentModelPtr->addBond(*atom1It, *atom2It);
                }
            }
        } while(++atom1It != atom1EndIt);
        
        return true;
    }
    
    void PDBParser::parse(molecule & mol, std::istream & stream) {
        currentModelPtr = nullptr;
        currentChainPtr = nullptr;
        currentCompoundPtr = nullptr;
        
        std::string recordName;
        
        while(std::getline(stream, line_)) {
            
            recordName = boost::trim_right_copy(column(1, 6));
            
            if(recordName.compare("MODEL") == 0) {
                handleMODELRecord(mol);
            } else if(recordName.compare("ATOM") == 0 || recordName.compare("HETATM") == 0) {
                handleATOMRecord(mol);
            } else if(recordName.compare("CONECT") == 0) {
                handleCONECTRecord(mol);
            } else if(recordName.compare("TER") == 0) {
                handleTERRecord(mol);
            }
        }
        
        currentModelPtr = nullptr;
        currentChainPtr = nullptr;
        currentCompoundPtr = nullptr;
    }
    
    std::string PDBParser::column(unsigned int start, unsigned int end) {
        return line_.substr(start - 1, end - start + 1);
    }
    
    float PDBParser::getReal(unsigned int start,  unsigned int end) {
        return static_cast<float>(strtod(column(start, end).c_str(), nullptr));
    }
    
    unsigned int PDBParser::getInteger(unsigned int start,  unsigned int end) {
        return static_cast<unsigned int>(strtol(column(start, end).c_str(), nullptr, 0));
    }
    
    char PDBParser::getChar(unsigned int start) {
        return column(start, start).at(0);
    }
    
    const PDBParser::ResidueBondPairMap PDBParser::resBondPairs({
        {"ALA", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "HB1"}, {"CB", "HB2"}, {"CB", "HB3"}, {"OXT", "HXT"}})},
        {"ARG", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "CD"}, {"CG", "HG2"}, {"CG", "HG3"}, {"CD", "NE"}, {"CD", "HD2"}, {"CD", "HD3"}, {"NE", "CZ"}, {"NE", "HE"}, {"CZ", "NH1"}, {"CZ", "NH2"}, {"NH1", "HH11"}, {"NH1", "HH12"}, {"NH2", "HH21"}, {"NH2", "HH22"}, {"OXT", "HXT"}})},
        {"ASN", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "OD1"}, {"CG", "ND2"}, {"ND2", "HD21"}, {"ND2", "HD22"}, {"OXT", "HXT"}})},
        {"ASP", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "OD1"}, {"CG", "OD2"}, {"OD2", "HD2"}, {"OXT", "HXT"}})},
        {"CYS", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "SG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"SG", "HG"}, {"OXT", "HXT"}})},
        {"GLN", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "CD"}, {"CG", "HG2"}, {"CG", "HG3"}, {"CD", "OE1"}, {"CD", "NE2"}, {"NE2", "HE21"}, {"NE2", "HE22"}, {"OXT", "HXT"}})},
        {"GLU", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "CD"}, {"CG", "HG2"}, {"CG", "HG3"}, {"CD", "OE1"}, {"CD", "OE2"}, {"OE2", "HE2"}, {"OXT", "HXT"}})},
        {"GLY", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "HA2"}, {"CA", "HA3"}, {"C", "O"}, {"C", "OXT"}, {"OXT", "HXT"}})},
        {"HIS", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "ND1"}, {"CG", "CD2"}, {"ND1", "CE1"}, {"ND1", "HD1"}, {"CD2", "NE2"}, {"CD2", "HD2"}, {"CE1", "NE2"}, {"CE1", "HE1"}, {"NE2", "HE2"}, {"OXT", "HXT"}})},
        {"ILE", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG1"}, {"CB", "CG2"}, {"CB", "HB"}, {"CG1", "CD1"}, {"CG1", "HG12"}, {"CG1", "HG13"}, {"CG2", "HG21"}, {"CG2", "HG22"}, {"CG2", "HG23"}, {"CD1", "HD11"}, {"CD1", "HD12"}, {"CD1", "HD13"}, {"OXT", "HXT"}})},
        {"LEU", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "CD1"}, {"CG", "CD2"}, {"CG", "HG"}, {"CD1", "HD11"}, {"CD1", "HD12"}, {"CD1", "HD13"}, {"CD2", "HD21"}, {"CD2", "HD22"}, {"CD2", "HD23"}, {"OXT", "HXT"}})},
        {"LYS", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "CD"}, {"CG", "HG2"}, {"CG", "HG3"}, {"CD", "CE"}, {"CD", "HD2"}, {"CD", "HD3"}, {"CE", "NZ"}, {"CE", "HE2"}, {"CE", "HE3"}, {"NZ", "HZ1"}, {"NZ", "HZ2"}, {"NZ", "HZ3"}, {"OXT", "HXT"}})},
        {"MET", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "SD"}, {"CG", "HG2"}, {"CG", "HG3"}, {"SD", "CE"}, {"CE", "HE1"}, {"CE", "HE2"}, {"CE", "HE3"}, {"OXT", "HXT"}})},
        {"PHE", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "CD1"}, {"CG", "CD2"}, {"CD1", "CE1"}, {"CD1", "HD1"}, {"CD2", "CE2"}, {"CD2", "HD2"}, {"CE1", "CZ"}, {"CE1", "HE1"}, {"CE2", "CZ"}, {"CE2", "HE2"}, {"CZ", "HZ"}, {"OXT", "HXT"}})},
        {"PRO", PDBParser::BondPairList({{"N", "CA"}, {"N", "CD"}, {"N", "H"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "CD"}, {"CG", "HG2"}, {"CG", "HG3"}, {"CD", "HD2"}, {"CD", "HD3"}, {"OXT", "HXT"}})},
        {"SER", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "OG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"OG", "HG"}, {"OXT", "HXT"}})},
        {"THR", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "OG1"}, {"CB", "CG2"}, {"CB", "HB"}, {"OG1", "HG1"}, {"CG2", "HG21"}, {"CG2", "HG22"}, {"CG2", "HG23"}, {"OXT", "HXT"}})},
        {"TRP", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "CD1"}, {"CG", "CD2"}, {"CD1", "NE1"}, {"CD1", "HD1"}, {"CD2", "CE2"}, {"CD2", "CE3"}, {"NE1", "CE2"}, {"NE1", "HE1"}, {"CE2", "CZ2"}, {"CE3", "CZ3"}, {"CE3", "HE3"}, {"CZ2", "CH2"}, {"CZ2", "HZ2"}, {"CZ3", "CH2"}, {"CZ3", "HZ3"}, {"CH2", "HH2"}, {"OXT", "HXT"}})},
        {"TYR", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG"}, {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "CD1"}, {"CG", "CD2"}, {"CD1", "CE1"}, {"CD1", "HD1"}, {"CD2", "CE2"}, {"CD2", "HD2"}, {"CE1", "CZ"}, {"CE1", "HE1"}, {"CE2", "CZ"}, {"CE2", "HE2"}, {"CZ", "OH"}, {"OH", "HH"}, {"OXT", "HXT"}})},
        {"VAL", PDBParser::BondPairList({{"N", "CA"}, {"N", "H"}, {"N", "H2"}, {"CA", "C"}, {"CA", "CB"}, {"CA", "HA"}, {"C", "O"}, {"C", "OXT"}, {"CB", "CG1"}, {"CB", "CG2"}, {"CB", "HB"}, {"CG1", "HG11"}, {"CG1", "HG12"}, {"CG1", "HG13"}, {"CG2", "HG21"}, {"CG2", "HG22"}, {"CG2", "HG23"}, {"OXT", "HXT"}})},
        {"DA", PDBParser::BondPairList({{"OP3", "P"}, {"OP3", "HOP3"}, {"P", "OP1"}, {"P", "OP2"}, {"P", "O5'"}, {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"}, {"C5'", "H5'"}, {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"}, {"C4'", "H4'"}, {"O4'", "C1'"}, {"C3'", "O3'"}, {"C3'", "C2'"}, {"C3'", "H3'"}, {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"}, {"C2'", "H2''"}, {"C1'", "N9"}, {"C1'", "H1'"}, {"N9", "C8"}, {"N9", "C4"}, {"C8", "N7"}, {"C8", "H8"}, {"N7", "C5"}, {"C5", "C6"}, {"C5", "C4"}, {"C6", "N6"}, {"C6", "N1"}, {"N6", "H61"}, {"N6", "H62"}, {"N1", "C2"}, {"C2", "N3"}, {"C2", "H2"}, {"N3", "C4"}})},
        {"DC", PDBParser::BondPairList({{"OP3", "P"}, {"OP3", "HOP3"}, {"P", "OP1"}, {"P", "OP2"}, {"P", "O5'"}, {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"}, {"C5'", "H5'"}, {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"}, {"C4'", "H4'"}, {"O4'", "C1'"}, {"C3'", "O3'"}, {"C3'", "C2'"}, {"C3'", "H3'"}, {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"}, {"C2'", "H2''"}, {"C1'", "N1"}, {"C1'", "H1'"}, {"N1", "C2"}, {"N1", "C6"}, {"C2", "O2"}, {"C2", "N3"}, {"N3", "C4"}, {"C4", "N4"}, {"C4", "C5"}, {"N4", "H41"}, {"N4", "H42"}, {"C5", "C6"}, {"C5", "H5"}, {"C6", "H6"}})},
        {"DG", PDBParser::BondPairList({{"OP3", "P"}, {"OP3", "HOP3"}, {"P", "OP1"}, {"P", "OP2"}, {"P", "O5'"}, {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"}, {"C5'", "H5'"}, {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"}, {"C4'", "H4'"}, {"O4'", "C1'"}, {"C3'", "O3'"}, {"C3'", "C2'"}, {"C3'", "H3'"}, {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"}, {"C2'", "H2''"}, {"C1'", "N9"}, {"C1'", "H1'"}, {"N9", "C8"}, {"N9", "C4"}, {"C8", "N7"}, {"C8", "H8"}, {"N7", "C5"}, {"C5", "C6"}, {"C5", "C4"}, {"C6", "O6"}, {"C6", "N1"}, {"N1", "C2"}, {"N1", "H1"}, {"C2", "N2"}, {"C2", "N3"}, {"N2", "H21"}, {"N2", "H22"}, {"N3", "C4"}})},
        {"DT", PDBParser::BondPairList({{"OP3", "P"}, {"OP3", "HOP3"}, {"P", "OP1"}, {"P", "OP2"}, {"P", "O5'"}, {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"}, {"C5'", "H5'"}, {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"}, {"C4'", "H4'"}, {"O4'", "C1'"}, {"C3'", "O3'"}, {"C3'", "C2'"}, {"C3'", "H3'"}, {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"}, {"C2'", "H2''"}, {"C1'", "N1"}, {"C1'", "H1'"}, {"N1", "C2"}, {"N1", "C6"}, {"C2", "O2"}, {"C2", "N3"}, {"N3", "C4"}, {"N3", "H3"}, {"C4", "O4"}, {"C4", "C5"}, {"C5", "C7"}, {"C5", "C6"}, {"C7", "H71"}, {"C7", "H72"}, {"C7", "H73"}, {"C6", "H6"}})},
        {"A", PDBParser::BondPairList({{"OP3", "P"}, {"OP3", "HOP3"}, {"P", "OP1"}, {"P", "OP2"}, {"P", "O5'"}, {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"}, {"C5'", "H5'"}, {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"}, {"C4'", "H4'"}, {"O4'", "C1'"}, {"C3'", "O3'"}, {"C3'", "C2'"}, {"C3'", "H3'"}, {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"}, {"C2'", "H2''"}, {"C1'", "N9"}, {"C1'", "H1'"}, {"N9", "C8"}, {"N9", "C4"}, {"C8", "N7"}, {"C8", "H8"}, {"N7", "C5"}, {"C5", "C6"}, {"C5", "C4"}, {"C6", "N6"}, {"C6", "N1"}, {"N6", "H61"}, {"N6", "H62"}, {"N1", "C2"}, {"C2", "N3"}, {"C2", "H2"}, {"N3", "C4"}})},
        {"C", PDBParser::BondPairList({{"OP3", "P"}, {"OP3", "HOP3"}, {"P", "OP1"}, {"P", "OP2"}, {"P", "O5'"}, {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"}, {"C5'", "H5'"}, {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"}, {"C4'", "H4'"}, {"O4'", "C1'"}, {"C3'", "O3'"}, {"C3'", "C2'"}, {"C3'", "H3'"}, {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"}, {"C2'", "H2''"}, {"C1'", "N1"}, {"C1'", "H1'"}, {"N1", "C2"}, {"N1", "C6"}, {"C2", "O2"}, {"C2", "N3"}, {"N3", "C4"}, {"C4", "N4"}, {"C4", "C5"}, {"N4", "H41"}, {"N4", "H42"}, {"C5", "C6"}, {"C5", "H5"}, {"C6", "H6"}})},
        {"G", PDBParser::BondPairList({{"OP3", "P"}, {"OP3", "HOP3"}, {"P", "OP1"}, {"P", "OP2"}, {"P", "O5'"}, {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"}, {"C5'", "H5'"}, {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"}, {"C4'", "H4'"}, {"O4'", "C1'"}, {"C3'", "O3'"}, {"C3'", "C2'"}, {"C3'", "H3'"}, {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"}, {"C2'", "H2''"}, {"C1'", "N9"}, {"C1'", "H1'"}, {"N9", "C8"}, {"N9", "C4"}, {"C8", "N7"}, {"C8", "H8"}, {"N7", "C5"}, {"C5", "C6"}, {"C5", "C4"}, {"C6", "O6"}, {"C6", "N1"}, {"N1", "C2"}, {"N1", "H1"}, {"C2", "N2"}, {"C2", "N3"}, {"N2", "H21"}, {"N2", "H22"}, {"N3", "C4"}})},
        {"U", PDBParser::BondPairList({{"OP3", "P"}, {"OP3", "HOP3"}, {"P", "OP1"}, {"P", "OP2"}, {"P", "O5'"}, {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"}, {"C5'", "H5'"}, {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"}, {"C4'", "H4'"}, {"O4'", "C1'"}, {"C3'", "O3'"}, {"C3'", "C2'"}, {"C3'", "H3'"}, {"O3'", "HO3'"}, {"C2'", "O2'"}, {"C2'", "C1'"}, {"C2'", "H2'"}, {"O2'", "HO2'"}, {"C1'", "N1"}, {"C1'", "H1'"}, {"N1", "C2"}, {"N1", "C6"}, {"C2", "O2"}, {"C2", "N3"}, {"N3", "C4"}, {"N3", "H3"}, {"C4", "O4"}, {"C4", "C5"}, {"C5", "C6"}, {"C5", "H5"}, {"C6", "H6"}})}
    });
    
}