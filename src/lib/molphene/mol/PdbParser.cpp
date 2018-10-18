#include <boost/algorithm/string/trim.hpp>
#include <cstdlib>

#include "Atom.hpp"
#include "Bond.hpp"
#include "Chain.hpp"
#include "Compound.hpp"
#include "Model.hpp"
#include "Molecule.hpp"
#include "PdbParser.hpp"

namespace molphene {

void
PdbParser::parse(Molecule* molptr, std::istream& stream)
{
  current_model_ptr_ = nullptr;
  current_chain_ptr_ = nullptr;
  current_compound_ptr_ = nullptr;

  std::string record;

  while(std::getline(stream, line_)) {
    record = boost::trim_right_copy(column_(1, 6));

    if(record == "MODEL") {
      handle_model_record_(molptr);
    } else if(record == "ATOM" || record == "HETATM") {
      handle_atom_record_(molptr);
    } else if(record == "CONECT") {
      handle_conect_record_(molptr);
    } else if(record == "TER") {
      handle_ter_record_(molptr);
    }
  }

  current_model_ptr_ = nullptr;
  current_chain_ptr_ = nullptr;
  current_compound_ptr_ = nullptr;
}

bool
PdbParser::build_bond_(Compound& comp1,
                       const std::string& atomName1,
                       Compound& comp2,
                       const std::string& atomName2)
{
  auto a1it = comp1.atoms_begin(atomName1);
  auto a1et = comp1.atoms_end(atomName1);

  if(a1it == a1et) {
    return false;
  }

  do {
    const auto aloc1 = a1it->altloc();
    auto a2it = comp2.atoms_begin(atomName2);
    auto a2et = comp2.atoms_end(atomName2);

    for(; a2it != a2et; ++a2it) {
      if(aloc1) {
        const auto aloc2 = a2it->altloc();
        if(aloc1 == aloc2) {
          current_model_ptr_->add_bond(*a1it, *a2it);
          break;
        }
      } else {
        current_model_ptr_->add_bond(*a1it, *a2it);
      }
    }
  } while(++a1it != a1et);

  return true;
}

std::string
PdbParser::column_(unsigned int start, unsigned int end)
{
  return line_.substr(start - 1, end - start + 1);
}

char
PdbParser::get_char_(unsigned int start)
{
  return column_(start, start).at(0);
}

unsigned int
PdbParser::get_int_(unsigned int start, unsigned int end)
{
  return static_cast<unsigned int>(
   strtol(column_(start, end).c_str(), nullptr, 0));
}

float
PdbParser::get_real_(unsigned int start, unsigned int end)
{
  return static_cast<float>(strtod(column_(start, end).c_str(), nullptr));
}

// COLUMNS        DATA  TYPE    FIELD        DEFINITION
// -------------------------------------------------------------------------------------
// 1 -  6        Record name   "ATOM  "
// 7 - 11        Integer       serial       Atom  serial number.
// 13 - 16        Atom          name         Atom name.
// 17             Character     altLoc       Alternate location indicator.
// 18 - 20        Residue name  resName      Residue name.
// 22             Character     chainID      Chain identifier.
// 23 - 26        Integer       resSeq       Residue sequence number.
// 27             AChar         iCode        Code for insertion of residues.
// 31 - 38        Real(8.3)     x            Orthogonal coordinates for X in
// Angstroms. 39 - 46        Real(8.3)     y            Orthogonal
// coordinates for Y in Angstroms. 47 - 54        Real(8.3)     z Orthogonal
// coordinates for Z in Angstroms. 55 - 60        Real(6.2)     occupancy
// Occupancy. 61 - 66        Real(6.2)     tempFactor   Temperature  factor.
// 77 - 78        LString(2)    element      Element symbol, right-justified.
// 79 - 80        LString(2)    charge       Charge  on the atom.
void
PdbParser::handle_atom_record_(Molecule* molptr)
{
  auto& mol = *molptr;
  const auto aserial = get_int_(7, 11);
  const auto aname = boost::trim_copy(column_(13, 16));
  const auto aloc = get_char_(17);
  const auto arname = boost::trim_copy(column_(18, 20));
  const auto acid = get_char_(22);
  const auto arseq = get_int_(23, 26);
  const auto aicode = column_(27, 27).at(0);
  const auto ax = get_real_(31, 38);
  const auto ay = get_real_(39, 46);
  const auto az = get_real_(47, 54);
  const auto ael = boost::trim_left_copy(column_(77, 78));

  if(!current_model_ptr_) {
    current_model_ptr_ = &mol.add_model();
    current_chain_ptr_ = nullptr;
  }

  if(!current_chain_ptr_ || current_chain_ptr_->id() != acid) {
    current_chain_ptr_ = current_model_ptr_->get_chain(acid);
    if(current_chain_ptr_ == nullptr) {
      current_chain_ptr_ = &current_model_ptr_->add_chain(acid);
    }
    current_compound_ptr_ = nullptr;
  }

  Compound::ResidueNumber resNum(arseq, arname, aicode);

  if(!current_compound_ptr_ || current_compound_ptr_->resnum() != resNum) {
    current_compound_ptr_ = current_chain_ptr_->get_compound(resNum);
    if(current_compound_ptr_ == nullptr) {
      current_compound_ptr_ = &current_chain_ptr_->add_compound(resNum);
    }
  }

  Atom& atom = current_compound_ptr_->add_atom(ael, aname, aserial);
  atom.position(ax, ay, az);
  atom.altloc(aloc);
}

// COLUMNS       DATA  TYPE      FIELD        DEFINITION
// -------------------------------------------------------------------------
// 1 -  6        Record name    "CONECT"
// 7 - 11       Integer        serial       Atom  serial number
// 12 - 16        Integer        serial       Serial number of bonded atom
// 17 - 21        Integer        serial       Serial  number of bonded atom
// 22 - 26        Integer        serial       Serial number of bonded atom
// 27 - 31        Integer        serial       Serial number of bonded atom
void
PdbParser::handle_conect_record_(Molecule* molptr)
{
  Molecule& mol = *molptr;
  const auto aser1 = get_int_(7, 11);

  for(auto& model : Molecule::ModelsIterable {mol}) {
    const auto atm1 = model.get_atom(aser1);

    for(auto i = 12u; i <= 27; i += 5) {
      const auto aser2 = get_int_(i, i + 4);
      if(!aser2) {
        break;
      }
      if(aser1 < aser2) {
        const auto atm2 = model.get_atom(aser2);
        model.add_bond(*atm1, *atm2);
      }
    }
  }
}

// COLUMNS        DATA  TYPE    FIELD          DEFINITION
// ---------------------------------------------------------------------------------------
// 1 -  6        Record name   "MODEL "
// 11 - 14        Integer       serial         Model serial number.
void
PdbParser::handle_model_record_(Molecule* molptr)
{
  Molecule& mol = *molptr;
  current_model_ptr_ = &mol.add_model();
  current_chain_ptr_ = nullptr;
}

// COLUMNS        DATA  TYPE    FIELD           DEFINITION
// -------------------------------------------------------------------------
// 1 -  6        Record name   "TER   "
// 7 - 11        Integer       serial          Serial number.
// 18 - 20        Residue name  resName         Residue name.
// 22             Character     chainID         Chain identifier.
// 23 - 26        Integer       resSeq          Residue sequence number.
// 27             AChar         iCode           Insertion code.
void
PdbParser::handle_ter_record_(Molecule* molptr)
{
  const PdbParser::ResidueBondPairsMap res_bond_pairs(
   {{"ALA",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "H"},
                           {"N", "H2"},
                           {"CA", "C"},
                           {"CA", "CB"},
                           {"CA", "HA"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"CB", "HB1"},
                           {"CB", "HB2"},
                           {"CB", "HB3"},
                           {"OXT", "HXT"}})},
    {"ARG",
     PdbParser::BondPairs(
      {{"N", "CA"},     {"N", "H"},      {"N", "H2"},     {"CA", "C"},
       {"CA", "CB"},    {"CA", "HA"},    {"C", "O"},      {"C", "OXT"},
       {"CB", "CG"},    {"CB", "HB2"},   {"CB", "HB3"},   {"CG", "CD"},
       {"CG", "HG2"},   {"CG", "HG3"},   {"CD", "NE"},    {"CD", "HD2"},
       {"CD", "HD3"},   {"NE", "CZ"},    {"NE", "HE"},    {"CZ", "NH1"},
       {"CZ", "NH2"},   {"NH1", "HH11"}, {"NH1", "HH12"}, {"NH2", "HH21"},
       {"NH2", "HH22"}, {"OXT", "HXT"}})},
    {"ASN",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "H"},
                           {"N", "H2"},
                           {"CA", "C"},
                           {"CA", "CB"},
                           {"CA", "HA"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"CB", "CG"},
                           {"CB", "HB2"},
                           {"CB", "HB3"},
                           {"CG", "OD1"},
                           {"CG", "ND2"},
                           {"ND2", "HD21"},
                           {"ND2", "HD22"},
                           {"OXT", "HXT"}})},
    {"ASP",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "H"},
                           {"N", "H2"},
                           {"CA", "C"},
                           {"CA", "CB"},
                           {"CA", "HA"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"CB", "CG"},
                           {"CB", "HB2"},
                           {"CB", "HB3"},
                           {"CG", "OD1"},
                           {"CG", "OD2"},
                           {"OD2", "HD2"},
                           {"OXT", "HXT"}})},
    {"CYS",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "H"},
                           {"N", "H2"},
                           {"CA", "C"},
                           {"CA", "CB"},
                           {"CA", "HA"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"CB", "SG"},
                           {"CB", "HB2"},
                           {"CB", "HB3"},
                           {"SG", "HG"},
                           {"OXT", "HXT"}})},
    {"GLN",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "H"},
                           {"N", "H2"},
                           {"CA", "C"},
                           {"CA", "CB"},
                           {"CA", "HA"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"CB", "CG"},
                           {"CB", "HB2"},
                           {"CB", "HB3"},
                           {"CG", "CD"},
                           {"CG", "HG2"},
                           {"CG", "HG3"},
                           {"CD", "OE1"},
                           {"CD", "NE2"},
                           {"NE2", "HE21"},
                           {"NE2", "HE22"},
                           {"OXT", "HXT"}})},
    {"GLU",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "H"},
                           {"N", "H2"},
                           {"CA", "C"},
                           {"CA", "CB"},
                           {"CA", "HA"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"CB", "CG"},
                           {"CB", "HB2"},
                           {"CB", "HB3"},
                           {"CG", "CD"},
                           {"CG", "HG2"},
                           {"CG", "HG3"},
                           {"CD", "OE1"},
                           {"CD", "OE2"},
                           {"OE2", "HE2"},
                           {"OXT", "HXT"}})},
    {"GLY",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "H"},
                           {"N", "H2"},
                           {"CA", "C"},
                           {"CA", "HA2"},
                           {"CA", "HA3"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"OXT", "HXT"}})},
    {"HIS",
     PdbParser::BondPairs({{"N", "CA"},    {"N", "H"},     {"N", "H2"},
                           {"CA", "C"},    {"CA", "CB"},   {"CA", "HA"},
                           {"C", "O"},     {"C", "OXT"},   {"CB", "CG"},
                           {"CB", "HB2"},  {"CB", "HB3"},  {"CG", "ND1"},
                           {"CG", "CD2"},  {"ND1", "CE1"}, {"ND1", "HD1"},
                           {"CD2", "NE2"}, {"CD2", "HD2"}, {"CE1", "NE2"},
                           {"CE1", "HE1"}, {"NE2", "HE2"}, {"OXT", "HXT"}})},
    {"ILE",
     PdbParser::BondPairs({{"N", "CA"},     {"N", "H"},      {"N", "H2"},
                           {"CA", "C"},     {"CA", "CB"},    {"CA", "HA"},
                           {"C", "O"},      {"C", "OXT"},    {"CB", "CG1"},
                           {"CB", "CG2"},   {"CB", "HB"},    {"CG1", "CD1"},
                           {"CG1", "HG12"}, {"CG1", "HG13"}, {"CG2", "HG21"},
                           {"CG2", "HG22"}, {"CG2", "HG23"}, {"CD1", "HD11"},
                           {"CD1", "HD12"}, {"CD1", "HD13"}, {"OXT", "HXT"}})},
    {"LEU",
     PdbParser::BondPairs({{"N", "CA"},     {"N", "H"},      {"N", "H2"},
                           {"CA", "C"},     {"CA", "CB"},    {"CA", "HA"},
                           {"C", "O"},      {"C", "OXT"},    {"CB", "CG"},
                           {"CB", "HB2"},   {"CB", "HB3"},   {"CG", "CD1"},
                           {"CG", "CD2"},   {"CG", "HG"},    {"CD1", "HD11"},
                           {"CD1", "HD12"}, {"CD1", "HD13"}, {"CD2", "HD21"},
                           {"CD2", "HD22"}, {"CD2", "HD23"}, {"OXT", "HXT"}})},
    {"LYS",
     PdbParser::BondPairs(
      {{"N", "CA"},   {"N", "H"},    {"N", "H2"},   {"CA", "C"},
       {"CA", "CB"},  {"CA", "HA"},  {"C", "O"},    {"C", "OXT"},
       {"CB", "CG"},  {"CB", "HB2"}, {"CB", "HB3"}, {"CG", "CD"},
       {"CG", "HG2"}, {"CG", "HG3"}, {"CD", "CE"},  {"CD", "HD2"},
       {"CD", "HD3"}, {"CE", "NZ"},  {"CE", "HE2"}, {"CE", "HE3"},
       {"NZ", "HZ1"}, {"NZ", "HZ2"}, {"NZ", "HZ3"}, {"OXT", "HXT"}})},
    {"MET",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "H"},
                           {"N", "H2"},
                           {"CA", "C"},
                           {"CA", "CB"},
                           {"CA", "HA"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"CB", "CG"},
                           {"CB", "HB2"},
                           {"CB", "HB3"},
                           {"CG", "SD"},
                           {"CG", "HG2"},
                           {"CG", "HG3"},
                           {"SD", "CE"},
                           {"CE", "HE1"},
                           {"CE", "HE2"},
                           {"CE", "HE3"},
                           {"OXT", "HXT"}})},
    {"PHE",
     PdbParser::BondPairs(
      {{"N", "CA"},    {"N", "H"},     {"N", "H2"},    {"CA", "C"},
       {"CA", "CB"},   {"CA", "HA"},   {"C", "O"},     {"C", "OXT"},
       {"CB", "CG"},   {"CB", "HB2"},  {"CB", "HB3"},  {"CG", "CD1"},
       {"CG", "CD2"},  {"CD1", "CE1"}, {"CD1", "HD1"}, {"CD2", "CE2"},
       {"CD2", "HD2"}, {"CE1", "CZ"},  {"CE1", "HE1"}, {"CE2", "CZ"},
       {"CE2", "HE2"}, {"CZ", "HZ"},   {"OXT", "HXT"}})},
    {"PRO",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "CD"},
                           {"N", "H"},
                           {"CA", "C"},
                           {"CA", "CB"},
                           {"CA", "HA"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"CB", "CG"},
                           {"CB", "HB2"},
                           {"CB", "HB3"},
                           {"CG", "CD"},
                           {"CG", "HG2"},
                           {"CG", "HG3"},
                           {"CD", "HD2"},
                           {"CD", "HD3"},
                           {"OXT", "HXT"}})},
    {"SER",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "H"},
                           {"N", "H2"},
                           {"CA", "C"},
                           {"CA", "CB"},
                           {"CA", "HA"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"CB", "OG"},
                           {"CB", "HB2"},
                           {"CB", "HB3"},
                           {"OG", "HG"},
                           {"OXT", "HXT"}})},
    {"THR",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "H"},
                           {"N", "H2"},
                           {"CA", "C"},
                           {"CA", "CB"},
                           {"CA", "HA"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"CB", "OG1"},
                           {"CB", "CG2"},
                           {"CB", "HB"},
                           {"OG1", "HG1"},
                           {"CG2", "HG21"},
                           {"CG2", "HG22"},
                           {"CG2", "HG23"},
                           {"OXT", "HXT"}})},
    {"TRP",
     PdbParser::BondPairs(
      {{"N", "CA"},    {"N", "H"},     {"N", "H2"},    {"CA", "C"},
       {"CA", "CB"},   {"CA", "HA"},   {"C", "O"},     {"C", "OXT"},
       {"CB", "CG"},   {"CB", "HB2"},  {"CB", "HB3"},  {"CG", "CD1"},
       {"CG", "CD2"},  {"CD1", "NE1"}, {"CD1", "HD1"}, {"CD2", "CE2"},
       {"CD2", "CE3"}, {"NE1", "CE2"}, {"NE1", "HE1"}, {"CE2", "CZ2"},
       {"CE3", "CZ3"}, {"CE3", "HE3"}, {"CZ2", "CH2"}, {"CZ2", "HZ2"},
       {"CZ3", "CH2"}, {"CZ3", "HZ3"}, {"CH2", "HH2"}, {"OXT", "HXT"}})},
    {"TYR",
     PdbParser::BondPairs(
      {{"N", "CA"},    {"N", "H"},     {"N", "H2"},    {"CA", "C"},
       {"CA", "CB"},   {"CA", "HA"},   {"C", "O"},     {"C", "OXT"},
       {"CB", "CG"},   {"CB", "HB2"},  {"CB", "HB3"},  {"CG", "CD1"},
       {"CG", "CD2"},  {"CD1", "CE1"}, {"CD1", "HD1"}, {"CD2", "CE2"},
       {"CD2", "HD2"}, {"CE1", "CZ"},  {"CE1", "HE1"}, {"CE2", "CZ"},
       {"CE2", "HE2"}, {"CZ", "OH"},   {"OH", "HH"},   {"OXT", "HXT"}})},
    {"VAL",
     PdbParser::BondPairs({{"N", "CA"},
                           {"N", "H"},
                           {"N", "H2"},
                           {"CA", "C"},
                           {"CA", "CB"},
                           {"CA", "HA"},
                           {"C", "O"},
                           {"C", "OXT"},
                           {"CB", "CG1"},
                           {"CB", "CG2"},
                           {"CB", "HB"},
                           {"CG1", "HG11"},
                           {"CG1", "HG12"},
                           {"CG1", "HG13"},
                           {"CG2", "HG21"},
                           {"CG2", "HG22"},
                           {"CG2", "HG23"},
                           {"OXT", "HXT"}})},
    {"DA",
     PdbParser::BondPairs(
      {{"OP3", "P"},    {"OP3", "HOP3"}, {"P", "OP1"},   {"P", "OP2"},
       {"P", "O5'"},    {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"},
       {"C5'", "H5'"},  {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"},
       {"C4'", "H4'"},  {"O4'", "C1'"},  {"C3'", "O3'"}, {"C3'", "C2'"},
       {"C3'", "H3'"},  {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"},
       {"C2'", "H2''"}, {"C1'", "N9"},   {"C1'", "H1'"}, {"N9", "C8"},
       {"N9", "C4"},    {"C8", "N7"},    {"C8", "H8"},   {"N7", "C5"},
       {"C5", "C6"},    {"C5", "C4"},    {"C6", "N6"},   {"C6", "N1"},
       {"N6", "H61"},   {"N6", "H62"},   {"N1", "C2"},   {"C2", "N3"},
       {"C2", "H2"},    {"N3", "C4"}})},
    {"DC",
     PdbParser::BondPairs(
      {{"OP3", "P"},    {"OP3", "HOP3"}, {"P", "OP1"},   {"P", "OP2"},
       {"P", "O5'"},    {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"},
       {"C5'", "H5'"},  {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"},
       {"C4'", "H4'"},  {"O4'", "C1'"},  {"C3'", "O3'"}, {"C3'", "C2'"},
       {"C3'", "H3'"},  {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"},
       {"C2'", "H2''"}, {"C1'", "N1"},   {"C1'", "H1'"}, {"N1", "C2"},
       {"N1", "C6"},    {"C2", "O2"},    {"C2", "N3"},   {"N3", "C4"},
       {"C4", "N4"},    {"C4", "C5"},    {"N4", "H41"},  {"N4", "H42"},
       {"C5", "C6"},    {"C5", "H5"},    {"C6", "H6"}})},
    {"DG",
     PdbParser::BondPairs(
      {{"OP3", "P"},    {"OP3", "HOP3"}, {"P", "OP1"},   {"P", "OP2"},
       {"P", "O5'"},    {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"},
       {"C5'", "H5'"},  {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"},
       {"C4'", "H4'"},  {"O4'", "C1'"},  {"C3'", "O3'"}, {"C3'", "C2'"},
       {"C3'", "H3'"},  {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"},
       {"C2'", "H2''"}, {"C1'", "N9"},   {"C1'", "H1'"}, {"N9", "C8"},
       {"N9", "C4"},    {"C8", "N7"},    {"C8", "H8"},   {"N7", "C5"},
       {"C5", "C6"},    {"C5", "C4"},    {"C6", "O6"},   {"C6", "N1"},
       {"N1", "C2"},    {"N1", "H1"},    {"C2", "N2"},   {"C2", "N3"},
       {"N2", "H21"},   {"N2", "H22"},   {"N3", "C4"}})},
    {"DT",
     PdbParser::BondPairs(
      {{"OP3", "P"},    {"OP3", "HOP3"}, {"P", "OP1"},   {"P", "OP2"},
       {"P", "O5'"},    {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"},
       {"C5'", "H5'"},  {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"},
       {"C4'", "H4'"},  {"O4'", "C1'"},  {"C3'", "O3'"}, {"C3'", "C2'"},
       {"C3'", "H3'"},  {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"},
       {"C2'", "H2''"}, {"C1'", "N1"},   {"C1'", "H1'"}, {"N1", "C2"},
       {"N1", "C6"},    {"C2", "O2"},    {"C2", "N3"},   {"N3", "C4"},
       {"N3", "H3"},    {"C4", "O4"},    {"C4", "C5"},   {"C5", "C7"},
       {"C5", "C6"},    {"C7", "H71"},   {"C7", "H72"},  {"C7", "H73"},
       {"C6", "H6"}})},
    {"A",
     PdbParser::BondPairs(
      {{"OP3", "P"},    {"OP3", "HOP3"}, {"P", "OP1"},   {"P", "OP2"},
       {"P", "O5'"},    {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"},
       {"C5'", "H5'"},  {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"},
       {"C4'", "H4'"},  {"O4'", "C1'"},  {"C3'", "O3'"}, {"C3'", "C2'"},
       {"C3'", "H3'"},  {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"},
       {"C2'", "H2''"}, {"C1'", "N9"},   {"C1'", "H1'"}, {"N9", "C8"},
       {"N9", "C4"},    {"C8", "N7"},    {"C8", "H8"},   {"N7", "C5"},
       {"C5", "C6"},    {"C5", "C4"},    {"C6", "N6"},   {"C6", "N1"},
       {"N6", "H61"},   {"N6", "H62"},   {"N1", "C2"},   {"C2", "N3"},
       {"C2", "H2"},    {"N3", "C4"}})},
    {"C",
     PdbParser::BondPairs(
      {{"OP3", "P"},    {"OP3", "HOP3"}, {"P", "OP1"},   {"P", "OP2"},
       {"P", "O5'"},    {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"},
       {"C5'", "H5'"},  {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"},
       {"C4'", "H4'"},  {"O4'", "C1'"},  {"C3'", "O3'"}, {"C3'", "C2'"},
       {"C3'", "H3'"},  {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"},
       {"C2'", "H2''"}, {"C1'", "N1"},   {"C1'", "H1'"}, {"N1", "C2"},
       {"N1", "C6"},    {"C2", "O2"},    {"C2", "N3"},   {"N3", "C4"},
       {"C4", "N4"},    {"C4", "C5"},    {"N4", "H41"},  {"N4", "H42"},
       {"C5", "C6"},    {"C5", "H5"},    {"C6", "H6"}})},
    {"G",
     PdbParser::BondPairs(
      {{"OP3", "P"},    {"OP3", "HOP3"}, {"P", "OP1"},   {"P", "OP2"},
       {"P", "O5'"},    {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"},
       {"C5'", "H5'"},  {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"},
       {"C4'", "H4'"},  {"O4'", "C1'"},  {"C3'", "O3'"}, {"C3'", "C2'"},
       {"C3'", "H3'"},  {"O3'", "HO3'"}, {"C2'", "C1'"}, {"C2'", "H2'"},
       {"C2'", "H2''"}, {"C1'", "N9"},   {"C1'", "H1'"}, {"N9", "C8"},
       {"N9", "C4"},    {"C8", "N7"},    {"C8", "H8"},   {"N7", "C5"},
       {"C5", "C6"},    {"C5", "C4"},    {"C6", "O6"},   {"C6", "N1"},
       {"N1", "C2"},    {"N1", "H1"},    {"C2", "N2"},   {"C2", "N3"},
       {"N2", "H21"},   {"N2", "H22"},   {"N3", "C4"}})},
    {"U",
     PdbParser::BondPairs(
      {{"OP3", "P"},   {"OP3", "HOP3"}, {"P", "OP1"},   {"P", "OP2"},
       {"P", "O5'"},   {"OP2", "HOP2"}, {"O5'", "C5'"}, {"C5'", "C4'"},
       {"C5'", "H5'"}, {"C5'", "H5''"}, {"C4'", "O4'"}, {"C4'", "C3'"},
       {"C4'", "H4'"}, {"O4'", "C1'"},  {"C3'", "O3'"}, {"C3'", "C2'"},
       {"C3'", "H3'"}, {"O3'", "HO3'"}, {"C2'", "O2'"}, {"C2'", "C1'"},
       {"C2'", "H2'"}, {"O2'", "HO2'"}, {"C1'", "N1"},  {"C1'", "H1'"},
       {"N1", "C2"},   {"N1", "C6"},    {"C2", "O2"},   {"C2", "N3"},
       {"N3", "C4"},   {"N3", "H3"},    {"C4", "O4"},   {"C4", "C5"},
       {"C5", "C6"},   {"C5", "H5"},    {"C6", "H6"}})}});

  if(current_chain_ptr_ == nullptr) {
    return;
  }

  auto prevr = static_cast<Compound*>(nullptr);
  for(auto& compnd : Chain::CompoundIterator {*current_chain_ptr_}) {
    const auto rname = compnd.name();
    const auto rbpit = res_bond_pairs.find(rname);

    if(rbpit != res_bond_pairs.cend()) {
      for(auto& bpair : rbpit->second) {
        build_bond_(compnd, bpair.first, compnd, bpair.second);
      }
    }

    if(prevr) {
      if(!build_bond_(*prevr, "C", compnd, "N")) {
        build_bond_(*prevr, "O3'", compnd, "P");
      }
    }

    prevr = &compnd;
  }

  current_chain_ptr_->terminate();
}

} // namespace molphene
