#include <cmath>
#include <sstream>
#include <string>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include "application.hpp"

namespace molphene {

void application::init_context()
{
  auto attrs = EmscriptenWebGLContextAttributes{};
  attrs.stencil = EM_TRUE;
  attrs.enableExtensionsByDefault = EM_FALSE;

  emscripten_webgl_init_context_attributes(&attrs);

  const auto ctx = emscripten_webgl_create_context(canvas_target, &attrs);

  emscripten_webgl_make_context_current(ctx);

  glctx = ctx;

  emscripten_webgl_enable_extension(glctx, "ANGLE_instanced_arrays");

  emscripten_set_mousedown_callback(
   canvas_target, this, false, &enable_drag_handler);
  emscripten_set_touchstart_callback(
   canvas_target, this, false, &enable_drag_handler);

  emscripten_set_mouseup_callback(
   canvas_target, this, false, &disable_drag_handler);
  emscripten_set_mouseleave_callback(
   canvas_target, this, false, &disable_drag_handler);
  emscripten_set_mouseout_callback(
   canvas_target, this, false, &disable_drag_handler);
  emscripten_set_touchend_callback(
   canvas_target, this, false, &disable_drag_handler);
  emscripten_set_touchcancel_callback(
   canvas_target, this, false, &disable_drag_handler);

  emscripten_set_mousemove_callback(
   canvas_target, this, false, &mouse_move_handler);
  emscripten_set_touchmove_callback(
   canvas_target, this, false, &mouse_move_handler);
};

auto application::framebuffer_size() const -> framebuffer_size_type
{
  int width;
  int height;
  emscripten_webgl_get_drawing_buffer_size(glctx, &width, &height);
  return std::make_pair(width, height);
}

void application::close_app()
{
}

} // namespace molphene
