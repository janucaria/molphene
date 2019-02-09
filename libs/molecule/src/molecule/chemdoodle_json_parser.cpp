#include <nlohmann/json.hpp>

#include "chemdoodle_json_parser.hpp"

#include "AtomInsertIterator.hpp"
#include "BondInsertIterator.hpp"

namespace molphene {

auto chemdoodle_json_parser::parse(const std::string& strjson) -> Molecule
{
  auto molecule = Molecule{};
  if(strjson.empty()) {
    return molecule;
  }

  auto jsonmol = nlohmann::json::parse(strjson);

  auto find_object_json_by_key =
   [](const auto& jsonmol,
      const std::string& key) -> std::optional<nlohmann::json::object_t> {
    const auto find_key = jsonmol.find(key);
    if(find_key == jsonmol.end()) {
      return std::nullopt;
    }

    const auto json_value = *find_key;

    if(!json_value.is_object()) {
      return std::nullopt;
    }

    return json_value;
  };

  auto pdb_json = find_object_json_by_key(jsonmol, "mol");
  if(pdb_json) {
    jsonmol = *pdb_json;
  }

  auto out_atoms = AtomInsertIterator{molecule};
  auto out_bonds = BondInsertIterator{molecule};

  auto find_array_json_by_key =
   [](const auto& jsonmol,
      const std::string& key) -> std::optional<nlohmann::json::array_t> {
    const auto find_array = jsonmol.find(key);
    if(find_array == jsonmol.end()) {
      return std::nullopt;
    }

    const auto json_array = *find_array;

    if(!json_array.is_array()) {
      return std::nullopt;
    }

    return json_array;
  };

  [find_array_json_by_key](const auto& jsonmol, auto outiter) {
    const auto json_atoms = find_array_json_by_key(jsonmol, "a");
    if(!json_atoms) {
      return;
    }

    boost::range::transform(*json_atoms, outiter, [](auto const json_atom) {
      auto const aelement = json_atom.template value<std::string>("l", "C");
      auto const ax = json_atom.template value<double>("x", 0);
      auto const ay = json_atom.template value<double>("y", 0);
      auto const az = json_atom.template value<double>("z", 0);

      auto atom = Atom{aelement, "", 0};
      atom.position(ax, ay, az);

      return atom;
    });
  }(jsonmol, out_atoms);

  [find_array_json_by_key](const auto& jsonmol, auto outiter) {
    const auto json_bonds = find_array_json_by_key(jsonmol, "b");
    if(!json_bonds) {
      return;
    }

    boost::range::transform(*json_bonds, outiter, [](auto const json_bond) {
      auto const ibegin = static_cast<int>(json_bond.at("b"));
      auto const iend = static_cast<int>(json_bond.at("e"));

      auto bond = Bond{ibegin, iend};

      return bond;
    });
  }(jsonmol, out_bonds);

  return molecule;
}

} // namespace molphene
