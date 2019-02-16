#ifndef MOLPHENE_VIEWPORT_HPP
#define MOLPHENE_VIEWPORT_HPP

namespace molphene {
template<typename size_type>
struct viewport {
  size_type x{0};
  size_type y{0};
  size_type width{0};
  size_type height{0};

  viewport() noexcept = default;

  viewport(size_type width, size_type height) noexcept
  : width{width}
  , height{height}
  {
  }
};
} // namespace molphene

#endif
