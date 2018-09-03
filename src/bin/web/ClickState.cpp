#include "ClickState.hpp"

namespace molphene {

ClickState::ClickState(bool is_down, long last_x, long last_y) noexcept
: is_down{is_down}
, last_x{last_x}
, last_y{last_y}
{
}

} // namespace molphene