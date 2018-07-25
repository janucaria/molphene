#ifndef __Molphene__PDBParser__
#define __Molphene__PDBParser__

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

#include "atom.h"
#include "bond.h"
#include "chain.h"
#include "compound.h"
#include "logger.h"
#include "model.h"
#include "molecule.h"

namespace molphene {
class PDBParser {
public:
  typedef std::pair<std::string, std::string> BondPair;
  typedef std::set<BondPair> BondPairList;
  typedef std::unordered_map<std::string, BondPairList> ResidueBondPairMap;

  PDBParser();

  void
  parse(molecule& mol, std::istream& stream);

private:
  const static ResidueBondPairMap resBondPairs;

  model* currentModelPtr;
  chain* currentChainPtr;
  compound* currentCompoundPtr;

  std::string line_;

  inline std::string
  column(unsigned int start, unsigned int end);

  float
  getReal(unsigned int start, unsigned int end);

  unsigned int
  getInteger(unsigned int start, unsigned int end);

  inline char
  getChar(unsigned int start);

  void
  handleATOMRecord(molecule& mol);

  void
  handleMODELRecord(molecule& mol);

  void
  handleCONECTRecord(molecule& mol);

  void
  handleTERRecord(molecule& mol);

  bool
  buildBond(compound& comp1,
            std::string atomName1,
            compound& comp2,
            std::string atomName2);
};
} // namespace molphene

#endif
