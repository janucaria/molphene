#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#include <glad/glad.h>
#endif

#include "application.hpp"

namespace molphene {

void application::init_context()
{
  glfwSetErrorCallback(
   [](int error, const char* description) { std::fputs(description, stderr); });

  if(!glfwInit()) {
    return;
  }

  int width = 640;
  int height = 480;

  auto* win_ptr =
   glfwCreateWindow(width, height, "Simple example", nullptr, nullptr);

  if(!win_ptr) {
    glfwTerminate();
    return;
  }

  window_.reset(win_ptr);

  glfwMakeContextCurrent(window_.get());

#ifndef __EMSCRIPTEN__
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
#endif

  glfwSetWindowUserPointer(window_.get(), this);

  glfwSetKeyCallback(
   window_.get(),
   [](GLFWwindow* window, int key, int scancode, int action, int mods) {
     auto app = static_cast<application*>(glfwGetWindowUserPointer(window));

     if(action == GLFW_PRESS) {
       auto charcode = key;
       if(charcode == GLFW_KEY_ESCAPE) {
         charcode = 27;
       }
       app->key_press_event(charcode, mods);
     }
   });

  glfwSetMouseButtonCallback(
   window_.get(), [](GLFWwindow* window, int button, int action, int mods) {
     auto app = static_cast<application*>(glfwGetWindowUserPointer(window));

     if(action == GLFW_PRESS) {
       auto pos_x = static_cast<double>(0);
       auto pos_y = static_cast<double>(0);
       glfwGetCursorPos(window, &pos_x, &pos_y);

       app->mouse_press_event(button, mods, pos_x, pos_y);
     } else {
       app->mouse_release_event(button, mods, 0, 0);
     }
   });

  glfwSetCursorPosCallback(
   window_.get(), [](GLFWwindow* window, double xpos, double ypos) {
     static_cast<application*>(glfwGetWindowUserPointer(window))
      ->mouse_move_event(static_cast<int>(xpos), static_cast<int>(ypos));
   });

  glfwSetScrollCallback(
   window_.get(), [](GLFWwindow* window, double xoffset, double yoffset) {
     static_cast<application*>(glfwGetWindowUserPointer(window))
      ->mouse_scroll_event(static_cast<int>(xoffset),
                           static_cast<int>(yoffset));
   });

  glfwSetFramebufferSizeCallback(
   window_.get(), [](GLFWwindow* window, int width, int height) {
     static_cast<application*>(glfwGetWindowUserPointer(window))
      ->framebuffer_size_change_event(width, height);
   });
}

void application::close_app()
{
  glfwSetWindowShouldClose(window_.get(), GL_TRUE);
}

void application::render_frame()
{
  base_application_type::render_frame();

  glfwSwapBuffers(window_.get());
  glfwPollEvents();
}

auto application::framebuffer_size() const -> framebuffer_size_type
{
  int width;
  int height;
  glfwGetFramebufferSize(window_.get(), &width, &height);
  return std::make_pair(width, height);
}

void application::run()
{
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(
   [](void* arg) { static_cast<application*>(arg)->render_frame(); },
   this,
   0,
   1);
#else
  while(!glfwWindowShouldClose(window_.get())) {
    render_frame();
  }
#endif
}

} // namespace molphene