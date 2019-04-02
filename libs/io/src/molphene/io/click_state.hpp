#ifndef MOLPHENE_IO_CLICK_STATE_HPP
#define MOLPHENE_IO_CLICK_STATE_HPP

#include <cstdlib>

namespace molphene::io {

class click_state {
public:
  bool is_down{};
  std::size_t last_x{};
  std::size_t last_y{};

  constexpr click_state() noexcept = default;

  constexpr click_state(bool is_down,
                        std::size_t last_x,
                        std::size_t last_y) noexcept
  : is_down{is_down}
  , last_x{last_x}
  , last_y{last_y}
  {
  }
};

} // namespace molphene::io

#endif
