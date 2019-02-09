#ifndef MOLPHENE_CHEMDOODLE_JSON_PARSER_HPP
#define MOLPHENE_CHEMDOODLE_JSON_PARSER_HPP

#include "stdafx.hpp"

#include "Molecule.hpp"

namespace molphene {

class chemdoodle_json_parser {
public:
  auto parse(const std::string& strjson) -> Molecule;
};

} // namespace molphene

#endif
