#include "application.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

namespace molphene {

auto application::init_context() -> bool
{
  glfwSetErrorCallback(
   [](int error, const char* description) { std::fputs(description, stderr); });

  if(!glfwInit()) {
    return false;
  }

  int width = 640;
  int height = 480;

  window_.reset(
   glfwCreateWindow(width, height, "Simple example", nullptr, nullptr));

  if(!window_) {
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window_.get());

  glfwSetWindowUserPointer(window_.get(), this);

  glfwSetKeyCallback(
   window_.get(),
   [](GLFWwindow* window, int key, int scancode, int action, int mods) {
     auto app = static_cast<application*>(glfwGetWindowUserPointer(window));

     if(action == GLFW_PRESS) {
       switch(key) {
       case GLFW_KEY_ESCAPE:
         glfwSetWindowShouldClose(window, GL_TRUE);
         break;
       case GLFW_KEY_P:
         app->camera.projection_mode(true);
         break;
       case GLFW_KEY_O:
         app->camera.projection_mode(false);
         break;
       case GLFW_KEY_K:
         app->scene.representation(molphene::molecule_display::spacefill,
                                   app->molecule);
         break;
       case GLFW_KEY_L:
         app->scene.representation(molphene::molecule_display::ball_and_stick,
                                   app->molecule);
         break;
       }
     }
   });

  glfwSetMouseButtonCallback(
   window_.get(), [](GLFWwindow* window, int button, int action, int mods) {
     auto app = static_cast<application*>(glfwGetWindowUserPointer(window));

     if(action == GLFW_PRESS) {
       auto last_x = static_cast<double>(0);
       auto last_y = static_cast<double>(0);
       glfwGetCursorPos(window, &last_x, &last_y);

       app->click_state.is_down = true;
       app->click_state.last_x = last_x;
       app->click_state.last_y = last_y;
     } else {
       app->click_state.is_down = false;
       app->click_state.last_x = 0;
       app->click_state.last_y = 0;
     }
   });

  glfwSetCursorPosCallback(
   window_.get(), [](GLFWwindow* window, double xpos, double ypos) {
     auto app = static_cast<application*>(glfwGetWindowUserPointer(window));

     if(app->click_state.is_down) {
       const auto delta_x = static_cast<double>(app->click_state.last_x) - xpos;
       const auto delta_y = static_cast<double>(app->click_state.last_y) - ypos;

       app->click_state.last_x = xpos;
       app->click_state.last_y = ypos;

       app->scene.rotate({M_PI * delta_y / 180, M_PI * delta_x / 180, 0});
     }
   });

  glfwSetScrollCallback(
   window_.get(), [](GLFWwindow* window, double xoffset, double yoffset) {
     auto app = static_cast<application*>(glfwGetWindowUserPointer(window));
     yoffset > 0 ? app->camera.zoom_in() : app->camera.zoom_out();
   });

  glfwSetFramebufferSizeCallback(
   window_.get(), [](GLFWwindow* window, int width, int height) {
     auto app = static_cast<application*>(glfwGetWindowUserPointer(window));

     app->renderer.change_dimension(width, height);
     app->camera.aspect_ratio(width, height);
     app->camera.update_view_matrix();
   });

  return true;
}

void application::open_pdb_data(std::string pdbdata)
{
  std::stringstream pdbstm;
  pdbstm.str(pdbdata);
  molecule = molphene::chemdoodle_json_parser{}.parse(pdbstm);

  scene.reset_mesh(molecule);
  camera.top = scene.bounding_sphere().radius() + 2;
  camera.update_view_matrix();
}

void application::canvas_size_change_callback(int width, int height)
{
  renderer.change_dimension(width, height);
  camera.aspect_ratio(width, height);
  camera.update_view_matrix();
}

void application::change_representation(int representation_type)
{
  switch(representation_type) {
  case static_cast<int>(molphene::molecule_display::spacefill): {
    scene.representation(molphene::molecule_display::spacefill, molecule);
  } break;
  case static_cast<int>(molphene::molecule_display::ball_and_stick): {
    scene.representation(molphene::molecule_display::ball_and_stick, molecule);
  } break;
  }
}

void application::render_frame()
{
  renderer.render(scene, camera);

  glfwSwapBuffers(window_.get());
  glfwPollEvents();
}

void application::setup()
{
  init_context();

  scene.setup_graphics();
  renderer.init();

  const auto [width, height] = [](auto window) noexcept
  {
    int width;
    int height;
    glfwGetFramebufferSize(window, &width, &height);
    return std::make_pair(width, height);
  }
  (window_.get());

  renderer.change_dimension(width, height);
  camera.aspect_ratio(width, height);
  camera.update_view_matrix();

  scene.reset_mesh(molecule);
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