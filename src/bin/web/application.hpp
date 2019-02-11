#ifndef MOLPHENE_APPLICATION_HPP
#define MOLPHENE_APPLICATION_HPP

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <molecule/Molecule.hpp>
#include <molecule/chemdoodle_json_parser.hpp>

#include <molphene/gl_renderer.hpp>
#include <molphene/scene.hpp>
#include <molphene/stdafx.hpp>

#include "click_state.hpp"

namespace molphene {

class application {
public:
  void init_context();

  void run();

  void open_pdb_data(std::string pdbdata);

  void canvas_size_change_callback(int width, int height);

  void change_representation(int representation_type);

  void render_frame();

private:
  click_state click_state{false, 0, 0};

  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE glctx{0};

  const char* canvas_target{"canvas"};

  molphene::scene scene{};

  molphene::gl_renderer renderer;

  molphene::scene::camera camera;

  molphene::Molecule molecule;

  template<typename T>
  static auto mouse_event(const T* event)
  {
    if constexpr(std::is_same_v<T, EmscriptenTouchEvent>) {
      if(event->numTouches < 1) {
        return static_cast<const EmscriptenTouchPoint*>(nullptr);
      }

      return std::addressof(event->touches[0]);
    } else {
      return event;
    }
  }

  template<typename T>
  static auto enable_drag_handler(int eventType, T* inEevent, void* userData)
   -> EM_BOOL
  {
    auto event = mouse_event(inEevent);
    auto app = static_cast<application*>(userData);

    if(event) {
      app->click_state.is_down = true;
      app->click_state.last_x = event->clientX;
      app->click_state.last_y = event->clientY;
    }

    return EM_TRUE;
  }

  template<typename T>
  static auto disable_drag_handler(int eventType, T* inEvent, void* userData)
   -> EM_BOOL
  {
    auto app = static_cast<application*>(userData);

    app->click_state.is_down = false;
    app->click_state.last_x = 0;
    app->click_state.last_y = 0;

    return EM_TRUE;
  }

  template<typename T>
  static auto mouse_move_handler(int eventType, T* inEvent, void* userData)
   -> EM_BOOL
  {
    auto event = mouse_event(inEvent);
    auto app = static_cast<application*>(userData);

    if(event && app->click_state.is_down) {
      const auto old_x = app->click_state.last_x;
      const auto old_y = app->click_state.last_y;

      app->click_state.last_x = event->clientX;
      app->click_state.last_y = event->clientY;

      const auto delta_x = static_cast<double>(app->click_state.last_x) - old_x;
      const auto delta_y = static_cast<double>(app->click_state.last_y) - old_y;

      app->scene.rotate({M_PI * delta_y / 180, M_PI * delta_x / 180, 0});
      app->render_frame();
    }

    return EM_TRUE;
  }
};
} // namespace molphene

#endif
