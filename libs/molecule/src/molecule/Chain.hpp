#ifndef MOLPHENE_MOLECULE_CHAIN_HPP
#define MOLPHENE_MOLECULE_CHAIN_HPP

#include "Compound.hpp"
#include <map>
#include <vector>

namespace molphene {
class Model;

class Chain {
  using Compounds = std::vector<Compound>;

  using CompoundMap = std::map<Compound::ResidueNumber, Compounds::size_type>;

public:
  class ResidueIterator;

  class CompoundIterator;

  class LiganIterator;

  using CompoundsIterator = Compounds::iterator;

  Chain(Model* model, char chainId);

  auto add_compound(const Compound::ResidueNumber& resnum) -> Compound&;

  auto get_compound(const Compound::ResidueNumber& resnum) -> Compound*;

  auto get_compound(unsigned int reseq, std::string resname, char icode)
   -> Compound*;

  auto compounds() const noexcept -> const Compounds&;

  auto id() const -> char;

  auto model() const -> Model&;

  void terminate();

private:
  char chain_id_;

  Compounds compounds_;

  Model* model_ptr_;

  CompoundMap res_lookup_;

  Compounds::size_type ter_{0};
};

class Chain::ResidueIterator {
public:
  explicit ResidueIterator(Chain& chain);

  auto begin() -> CompoundsIterator;

  auto end() -> CompoundsIterator;

private:
  Chain& chain_;
};

class Chain::CompoundIterator {
public:
  explicit CompoundIterator(Chain& chain);

  auto begin() -> CompoundsIterator;

  auto end() -> CompoundsIterator;

private:
  Chain& chain_;
};

class Chain::LiganIterator {
public:
  explicit LiganIterator(Chain& chain);

  auto begin() -> CompoundsIterator;

  auto end() -> CompoundsIterator;

private:
  Chain& chain_;
};
} // namespace molphene

#endif
