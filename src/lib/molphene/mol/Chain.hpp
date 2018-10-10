#ifndef MOLPHENE_MOL_CHAIN_HPP
#define MOLPHENE_MOL_CHAIN_HPP

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

  Compound&
  add_compound(const Compound::ResidueNumber& resnum);

  Compound*
  get_compound(const Compound::ResidueNumber& resnum);

  Compound*
  get_compound(unsigned int reseq, std::string resname, char icode);

  const Compounds&
  compounds() const noexcept;

  char
  id() const;

  Model&
  model() const;

  void
  terminate();

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

  Chain::CompoundsIterator
  begin();

  Chain::CompoundsIterator
  end();

private:
  Chain& chain_;
};

class Chain::CompoundIterator {
public:
  explicit CompoundIterator(Chain& chain);

  Chain::CompoundsIterator
  begin();

  Chain::CompoundsIterator
  end();

private:
  Chain& chain_;
};

class Chain::LiganIterator {
public:
  explicit LiganIterator(Chain& chain);

  Chain::CompoundsIterator
  begin();

  Chain::CompoundsIterator
  end();

private:
  Chain& chain_;
};
} // namespace molphene

#endif
