#include "logger.h"
#include "mol_parser.h"

#include <boost/algorithm/string/trim.hpp>

namespace molphene {
    
    mol_parser::mol_parser() {
        
    }
    
    
    void mol_parser::parse(molecule &mol, std::istream &stream) {
        
        std::string recordName;
        
        // read 1st row
        std::getline(stream, line_);
        
        // read 2nd row
        std::getline(stream, line_);
        
        // skip blank line
        std::getline(stream, line_);
        
        // calculate count row
        std::getline(stream, line_);
        
        // aaabbblllfffcccsssxxxrrrpppiiimmmvvvvvv
        
        //aaa = number of atoms (current max 255)* [Generic]
        unsigned int number_of_atoms = get_int(1, 3);
        
        //bbb = number of bonds (current max 255)* [Generic]
        unsigned int number_of_bonds = get_int(4, 6);
        
        //lll = number of atom lists (max 30)* [Query]
//        unsigned int number_of_atom_lists = get_int(7, 9);
        
        //fff = (obsolete)
        
        //ccc = chiral flag: 0=not chiral, 1=chiral [Generic]
//        bool chiral = get_int(13, 15) == 1;
        
        //sss = number of stext entries [MDL
        //                               ISIS/Desktop]
//        unsigned int number_of_stext_entries = get_int(16, 18);
        
        //xxx = (obsolete)
        
        //rrr = (obsolete)
        
        //ppp = (obsolete)
        
        //iii = (obsolete)
        
        //mmm = number of lines of additional properties,
        //including the M END line. No longer
        //supported, the default is set to 999.
        //[Generic]
//        unsigned int number_of_etcs = get_int(31, 33);
        
        //* These limits apply to MACCS-II, REACCS, and the MDL ISIS/Host Reaction
        //Gateway, but not to the MDL ISIS/Host Molecule Gateway or MDL ISIS/Desktop
        
//        LOG_D("Number of atoms : %d.", number_of_atoms);
//        LOG_D("Number of bonds : %d.", number_of_bonds);
//        LOG_D("Number of stext entries : %d.", number_of_stext_entries);
//        LOG_D("Number of atom lists : %d.", number_of_atom_lists);
//        LOG_D("Number of etc : %d.", number_of_etcs);
//        LOG_D("Chiral? %d.", chiral);
        
        model & mdl = mol.addModel();
        chain & chn = mdl.addChain('A');
        chn.terminate();
        
        current_compound = &chn.addCompound(std::make_tuple(0, "UNK", 'A'));
        
        // read each atoms
        for(unsigned int i = 0, as = 0; std::getline(stream, line_); ++i) {
            if(i < number_of_atoms) {
                // read atoms record
                read_atoms_record(++as);
            } else if(i - number_of_atoms < number_of_bonds) {
                // read bonds record
                read_bonds_record(mol);
            }
            
        }
    }
    
    void mol_parser::read_atoms_record(unsigned int serial) {
        // xxxxx.xxxxyyyyy.yyyyzzzzz.zzzz aaaddcccssshhhbbbvvvHHHrrriiimmmnnneee
        
        // xxxxx.xxxx float 1-10
        float ax = get_real(1, 10);
        
        // yyyyy.yyyy float 11 - 20
        float ay = get_real(11, 20);
        
        // zzzzz.zzzz float 21 - 30
        float az = get_real(21, 30);
        
        // aaa string 31 - 34
        std::string asymb = boost::trim_copy(column(31, 34));
        
        atom & atm = current_compound->addAtom(asymb, asymb, serial);
        atm.setPosition(ax, ay, az);
        
        // dd int 35 - 36
        
        // ccc int 37 - 39
        
        // sss int 40 - 42
        
        // hhh int 43 - 45
        
        // bbb int 46 - 48
        
        // vvv int 49 - 51
        
        // HHH int 52 - 54
        
        // rrr ?
        
        // iii ?
        
        // mmm int
        
        // nnn int
        
        // eee int
        
    }
    
    void mol_parser::read_bonds_record(molecule & mol) {
        
        // 111222tttsssxxxrrrccc
        
        // 111 int
        unsigned int a1 = get_int(1, 3);
        
        // 222 int
        unsigned int a2 = get_int(4, 6);
        
        // ttt int
        
        // sss int
        
        // xxx int
        
        // rrr ?
        
        // ccc int
        
        molecule::model_iterator modelIt = mol.mdlbegin();
        molecule::model_iterator modelEndIt = mol.mdlend();
        
        for( ; modelIt != modelEndIt; ++modelIt) {
            atom * atm1 = modelIt->getAtomBySerial(a1);
            atom * atm2 = modelIt->getAtomBySerial(a2);
            modelIt->addBond(*atm1, *atm2);
        }
    }
    
    std::string mol_parser::column(int start, int end) {
        return line_.substr(start - 1, end - start + 1);
    }
    
    float mol_parser::get_real(int start, int end) {
        return static_cast<float>(strtod(column(start, end).c_str(), nullptr));
    }
    
    int mol_parser::get_int(int start, int end) {
        return static_cast<int>(strtol(column(start, end).c_str(), nullptr, 0));
    }
    
}