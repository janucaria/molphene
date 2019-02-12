#include <nlohmann/json.hpp>

#include "chemdoodle_json_parser.hpp"

#include "atom_insert_iterator.hpp"
#include "bond_insert_iterator.hpp"

namespace molphene {


auto chemdoodle_json_parser::parse(std::istream& is) -> molecule
{
  const auto strjson = std::string{std::istreambuf_iterator<char>{is}, {}};
  return parse(strjson);
}

auto chemdoodle_json_parser::parse(std::string_view strjson) -> molecule
{
  auto mol = molecule{};
  if(strjson.empty()) {
    return mol;
  }

  auto jsonmol = nlohmann::json::parse(strjson);

  auto find_object_json_by_key =
   [](const auto& jsonmol, std::string_view key) -> std::optional<nlohmann::json::object_t> {
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

  auto out_atoms = atom_insert_iterator{mol};
  auto out_bonds = bond_insert_iterator{mol};

  auto find_array_json_by_key =
   [](const auto& jsonmol, std::string_view key) -> std::optional<nlohmann::json::array_t> {
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

      auto atm = atom{aelement, "", 0};
      atm.position(ax, ay, az);

      return atm;
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

      auto bnd = bond{ibegin, iend};

      return bnd;
    });
  }(jsonmol, out_bonds);

  return mol;
}

} // namespace molphene
