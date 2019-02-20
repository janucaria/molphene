#include "click_state.hpp"

namespace molphene::io {

click_state::click_state(bool is_down,
                         std::size_t last_x,
                         std::size_t last_y) noexcept
: is_down{is_down}
, last_x{last_x}
, last_y{last_y}
{
}

} // namespace molphene