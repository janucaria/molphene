#include <cmath>
#include <sstream>
#include <string>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include "Application.hpp"

namespace molphene {

void Application::open_pdb_data(std::string pdbdata)
{
  std::stringstream pdbstm;
  pdbstm.str(pdbdata);

  scene.open_stream(pdbstm);
  scene.reset_mesh();
  camera.top = scene.bounding_sphere().radius() + 2;
  camera.update_view_matrix();
  render_frame();
}

void Application::canvas_size_change_callback(int width, int height)
{
  scene.change_dimension(width, height);
  camera.aspect_ratio(width, height);
  camera.update_view_matrix();
  render_frame();
}

void Application::render_frame()
{
  renderer.render(scene, camera);
}

void Application::init_context()
{
  const auto attrs = []() {
    auto attrs = EmscriptenWebGLContextAttributes{};
    emscripten_webgl_init_context_attributes(&attrs);
    attrs.stencil = true;
    return attrs;
  }();

  const auto ctx = emscripten_webgl_create_context(canvas_target, &attrs);

  emscripten_webgl_make_context_current(ctx);

  glctx = ctx;

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

void Application::run()
{
  init_context();

  scene.setup_graphics();
  renderer.init();

  const auto [width, height] = [](auto glctx) noexcept
  {
    int width;
    int height;
    emscripten_webgl_get_drawing_buffer_size(glctx, &width, &height);
    return std::make_tuple(width, height);
  }
  (glctx);

  scene.change_dimension(width, height);
  camera.aspect_ratio(width, height);
  camera.update_view_matrix();

  auto pdbstm = std::stringstream{};

  scene.open_stream(pdbstm);
  scene.reset_mesh();
  camera.top = scene.bounding_sphere().radius() + 2;
  camera.update_view_matrix();
  render_frame();
}

} // namespace molphene
