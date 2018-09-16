#include "GlRenderer.hpp"

namespace molphene {

void
GlRenderer::init() noexcept
{
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glEnable(GL_DEPTH_TEST);

  color_light_shader_.init_program();
}

} // namespace molphene
