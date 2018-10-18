#ifndef MOLPHENE_MOL_PDB_PARSER_HPP
#define MOLPHENE_MOL_PDB_PARSER_HPP

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

#include "Compound.hpp"
#include "Molecule.hpp"

namespace molphene {
class PdbParser {
  using BondPair = std::pair<std::string, std::string>;

  using BondPairs = std::set<BondPair>;

  using ResidueBondPairsMap = std::unordered_map<std::string, BondPairs>;

public:
  void
  parse(Molecule* molptr, std::istream& stream);

private:
  Chain* current_chain_ptr_ {nullptr};

  Compound* current_compound_ptr_ {nullptr};

  Model* current_model_ptr_ {nullptr};

  std::string line_;

  bool
  build_bond_(Compound& comp1,
              const std::string& atomName1,
              Compound& comp2,
              const std::string& atomName2);

  inline std::string
  column_(unsigned int start, unsigned int end);

  inline char
  get_char_(unsigned int start);

  unsigned int
  get_int_(unsigned int start, unsigned int end);

  float
  get_real_(unsigned int start, unsigned int end);

  void
  handle_atom_record_(Molecule* molptr);

  void
  handle_conect_record_(Molecule* molptr);

  void
  handle_model_record_(Molecule* molptr);

  void
  handle_ter_record_(Molecule* molptr);
};
} // namespace molphene

#endif
