#ifndef MOLPHENE_GLFW_APPLICATION_HPP
#define MOLPHENE_GLFW_APPLICATION_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <molecule/chemdoodle_json_parser.hpp>
#include <molecule/molecule.hpp>

#include <molphene/gl_renderer.hpp>
#include <molphene/scene.hpp>
#include <molphene/stdafx.hpp>

#include "click_state.hpp"

namespace molphene {

class application {
  struct glfw_window_guard {
    void operator()(GLFWwindow* window) const noexcept
    {
      glfwDestroyWindow(window);
      glfwTerminate();
    }
  };

  using glfw_window_pointer = std::unique_ptr<GLFWwindow, glfw_window_guard>;

public:
  bool init_context();

  void setup();

  void run();

  void open_pdb_data(std::string pdbdata);

  void canvas_size_change_callback(int width, int height);

  void change_representation(int representation_type);

  void render_frame();

private:

  click_state click_state{false, 0, 0};

  glfw_window_pointer window_;

  molphene::scene scene{};

  molphene::gl_renderer renderer;

  molphene::scene::camera camera;

  molphene::molecule molecule;
};

} // namespace molphene

#endif
