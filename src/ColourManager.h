#ifndef __Molphene__ColourManager__
#define __Molphene__ColourManager__

#include "m3d.hpp"
#include <string>
#include <unordered_map>

namespace molphene {
class ColourManager {
public:
  ColourManager();

  const colour&
  getElementColor(std::string elementSymbol);
  const colour&
  getAltlocColor(char altloc);

private:
  std::unordered_map<std::string, colour> elementColors;
  std::unordered_map<char, colour> altlocColors;
};
} // namespace molphene

#endif
