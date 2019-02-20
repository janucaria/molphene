#ifndef MOLPHENE_GLFW_APPLICATION_HPP
#define MOLPHENE_GLFW_APPLICATION_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <molphene/basic_application.hpp>

namespace molphene {

class application : public basic_application<application> {
  struct glfw_window_guard {
    void operator()(GLFWwindow* window) const noexcept
    {
      glfwDestroyWindow(window);
      glfwTerminate();
    }
  };

  using glfw_window_pointer = std::unique_ptr<GLFWwindow, glfw_window_guard>;

  using base_application_type = basic_application<application>;

public:
  using framebuffer_size_type = std::pair<std::size_t, std::size_t>;

  void init_context();

  void run();

  void render_frame();

  auto framebuffer_size() const -> framebuffer_size_type;

  void close_app();

private:
  glfw_window_pointer window_;
};

} // namespace molphene

#endif
