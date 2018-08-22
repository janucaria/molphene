#ifndef MOLPHENE_MOL_CHAIN_HPP
#define MOLPHENE_MOL_CHAIN_HPP

#include "Compound.hpp"
#include <map>
#include <vector>

namespace molphene {
class Model;

class Chain {
  using Compounds = std::vector<Compound>;

  using Compound_map =
   std::map<Compound::Residue_number, Compounds::size_type>;

public:
  class Residue_iterator;

  class Compound_iterator;

  class Ligan_iterator;

  using Compounds_iterator = Compounds::iterator;

  Chain(Model* model, char chainId);

  Compound&
  add_compound(const Compound::Residue_number& resnum);

  Compound*
  get_compound(const Compound::Residue_number& resnum);

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

  Compound_map res_lookup_;

  Compounds::size_type ter_{0};
};

class Chain::Residue_iterator {
public:
  explicit Residue_iterator(Chain& chain);

  Chain::Compounds_iterator
  begin();

  Chain::Compounds_iterator
  end();

private:
  Chain& chain_;
};

class Chain::Compound_iterator {
public:
  explicit Compound_iterator(Chain& chain);

  Chain::Compounds_iterator
  begin();

  Chain::Compounds_iterator
  end();

private:
  Chain& chain_;
};

class Chain::Ligan_iterator {
public:
  explicit Ligan_iterator(Chain& chain);

  Chain::Compounds_iterator
  begin();

  Chain::Compounds_iterator
  end();

private:
  Chain& chain_;
};
} // namespace molphene

#endif
