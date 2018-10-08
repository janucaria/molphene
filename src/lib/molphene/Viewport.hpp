#ifndef MOLPHENE_VIEWPORT_HPP
#define MOLPHENE_VIEWPORT_HPP


namespace molphene
{
  template<typename size_t, typename float_t>
  struct Viewport {
    size_t x{0};
    size_t y{0};
    float_t width{0};
    float_t height{0};

    Viewport() noexcept = default;

    Viewport(float_t width, float_t height) noexcept
    : width{width}
    , height{height}
    {
    }
  };
} // molphene




#endif
