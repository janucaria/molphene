#ifndef MOLPHENE_COLOUR_MANAGER_HPP
#define MOLPHENE_COLOUR_MANAGER_HPP

#include "stdafx.hpp"

#include "m3d.hpp"

namespace molphene {

class color_manager {
public:
  color_manager();

  auto get_element_color(std::string_view esymbol) const noexcept -> rgba8;

private:
  std::unordered_map<std::string, rgba8> element_colors_;
};
} // namespace molphene

#endif
