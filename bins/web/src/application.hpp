#ifndef MOLPHENE_APPLICATION_HPP
#define MOLPHENE_APPLICATION_HPP

#include <utility>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <molecule/chemdoodle_json_parser.hpp>
#include <molecule/molecule.hpp>

#include <molphene/gl_renderer.hpp>
#include <molphene/scene.hpp>
#include <molphene/stdafx.hpp>

#include <molphene/io/click_state.hpp>

#include <molphene/basic_application.hpp>

namespace molphene {

class application : public basic_application<application> {
public:
  using framebuffer_size_type = std::pair<std::size_t, std::size_t>;

  void init_context();

  auto framebuffer_size() const -> framebuffer_size_type;

  void close_app();

private:
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE glctx{0};

  const char* canvas_target{"#canvas"};

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
      app->click_state().is_down = true;
      app->click_state().last_x = event->clientX;
      app->click_state().last_y = event->clientY;
    }

    return EM_TRUE;
  }

  template<typename T>
  static auto disable_drag_handler(int eventType, T* inEvent, void* userData)
   -> EM_BOOL
  {
    auto app = static_cast<application*>(userData);

    app->click_state().is_down = false;
    app->click_state().last_x = 0;
    app->click_state().last_y = 0;

    return EM_TRUE;
  }

  template<typename T>
  static auto mouse_move_handler(int eventType, T* inEvent, void* userData)
   -> EM_BOOL
  {
    auto event = mouse_event(inEvent);
    auto app = static_cast<application*>(userData);

    if(event && app->click_state().is_down) {
      const auto delta_x =
       static_cast<double>(app->click_state().last_x) - event->clientX;
      const auto delta_y =
       static_cast<double>(app->click_state().last_y) - event->clientY;

      app->click_state().last_x = event->clientX;
      app->click_state().last_y = event->clientY;

      app->scene().rotate({M_PI * delta_y / 180, M_PI * delta_x / 180, 0});
      app->render_frame();
    }

    return EM_TRUE;
  }
};
} // namespace molphene

#endif
