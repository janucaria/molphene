#ifndef MOLPHENE_CLICK_STATE_HPP
#define MOLPHENE_CLICK_STATE_HPP

namespace molphene {

struct ClickState {
  bool is_down;
  long last_x;
  long last_y;

  ClickState() noexcept = default;

  ClickState(bool is_down, long last_x, long last_y) noexcept;
};

} // namespace molphene

#endif
