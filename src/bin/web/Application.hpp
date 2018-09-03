#ifndef MOLPHENE_APPLICATION_HPP
#define MOLPHENE_APPLICATION_HPP

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <molphene/Scene.hpp>
#include <molphene/stdafx.hpp>

#include "ClickState.hpp"

namespace molphene {

class Application {
public:
  Application() noexcept;

  void
  init_context();

  void
  run();

  void open_pdb_data(std::string pdbdata);

  void canvas_size_change_callback(int width, int height);

private:
  ClickState click_state{false, 0, 0};

  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE glctx{0};

  const char* canvas_target{"canvas"};

  molphene::Scene scene{};

  static EM_BOOL
  enable_drag_handler(int eventType,
                      const EmscriptenMouseEvent* mouseEvent,
                      void* userData);

  static EM_BOOL
  enable_drag_handler(int eventType,
                      const EmscriptenTouchEvent* mouseEvent,
                      void* userData);

  static EM_BOOL
  disable_drag_handler(int eventType,
                       const EmscriptenMouseEvent* mouseEvent,
                       void* userData);

  static EM_BOOL
  disable_drag_handler(int eventType,
                       const EmscriptenTouchEvent* mouseEvent,
                       void* userData);

  static EM_BOOL
  mouse_move_handler(int eventType,
                     const EmscriptenMouseEvent* mouseEvent,
                     void* userData);

  static EM_BOOL
  mouse_move_handler(int eventType,
                     const EmscriptenTouchEvent* mouseEvent,
                     void* userData);
};
} // namespace molphene

#endif
