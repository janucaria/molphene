#ifndef MOLPHENE_IO_CLICK_STATE_HPP
#define MOLPHENE_IO_CLICK_STATE_HPP

#include <cstdlib>

namespace molphene::io {

class click_state {
public:
  bool is_down;
  std::size_t last_x;
  std::size_t last_y;

  click_state() noexcept = default;

  click_state(bool is_down, std::size_t last_x, std::size_t last_y) noexcept;
};

} // namespace molphene::io

#endif
