#ifndef MOLPHENE_VIEWPORT_HPP
#define MOLPHENE_VIEWPORT_HPP

namespace molphene {
template<typename size_t>
struct Viewport {
  size_t x{0};
  size_t y{0};
  size_t width{0};
  size_t height{0};

  Viewport() noexcept = default;

  Viewport(size_t width, size_t height) noexcept
  : width{width}
  , height{height}
  {
  }
};
} // namespace molphene

#endif
