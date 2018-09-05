#include "ClickState.hpp"

namespace molphene {

ClickState::ClickState(bool is_down, size_t last_x, size_t last_y) noexcept
: is_down{is_down}
, last_x{last_x}
, last_y{last_y}
{
}

} // namespace molphene