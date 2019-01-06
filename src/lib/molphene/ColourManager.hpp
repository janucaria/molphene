#ifndef MOLPHENE_COLOUR_MANAGER_HPP
#define MOLPHENE_COLOUR_MANAGER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"

namespace molphene {

class ColourManager {
public:
  ColourManager();

  auto get_element_color(const std::string& esymbol) const noexcept -> Rgba8;

private:
  std::unordered_map<std::string, Rgba8> element_colors_;
};
} // namespace molphene

#endif
