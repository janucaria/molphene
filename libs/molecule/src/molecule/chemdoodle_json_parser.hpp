#ifndef MOLPHENE_CHEMDOODLE_JSON_PARSER_HPP
#define MOLPHENE_CHEMDOODLE_JSON_PARSER_HPP

#include "stdafx.hpp"

#include "molecule.hpp"

namespace molphene {

class chemdoodle_json_parser {
public:
  auto parse(std::istream& is) -> molecule;

  auto parse(const std::string& strjson) -> molecule;
};

} // namespace molphene

#endif
