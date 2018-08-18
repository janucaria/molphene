#ifndef MOLPHENE_COLOUR_MANAGER_HPP
#define MOLPHENE_COLOUR_MANAGER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"

namespace molphene {

class Colour_manager {
public:
  Colour_manager();

  Rgba8
  get_element_color(const std::string& esymbol) const noexcept;

private:
  std::unordered_map<std::string, Rgba8> element_colors_;
};
} // namespace molphene

#endif
