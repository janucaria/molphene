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
  void parse(Molecule* molptr, std::istream& stream);

private:
  Chain* current_chain_ptr_{nullptr};

  Compound* current_compound_ptr_{nullptr};

  Model* current_model_ptr_{nullptr};

  std::string line_;

  auto build_bond_(Compound& comp1,
                   const std::string& atomName1,
                   Compound& comp2,
                   const std::string& atomName2) -> bool;

  inline auto column_(unsigned int start, unsigned int end) -> std::string;

  inline auto get_char_(unsigned int start) -> char;

  auto get_int_(unsigned int start, unsigned int end) -> unsigned int;

  auto get_real_(unsigned int start, unsigned int end) -> float;

  void handle_atom_record_(Molecule* molptr);

  void handle_conect_record_(Molecule* molptr);

  void handle_model_record_(Molecule* molptr);

  void handle_ter_record_(Molecule* molptr);
};
} // namespace molphene

#endif
