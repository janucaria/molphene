#ifndef MOLPHENE_CLICK_STATE_HPP
#define MOLPHENE_CLICK_STATE_HPP

#include <molphene/stdafx.hpp>

namespace molphene {

class click_state {
public:
  bool is_down;
  size_t last_x;
  size_t last_y;

  click_state() noexcept = default;

  click_state(bool is_down, size_t last_x, size_t last_y) noexcept;
};

} // namespace molphene

#endif
