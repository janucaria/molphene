#include "application.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

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

  auto* win_ptr = glfwCreateWindow(width, height, "Simple example", nullptr, nullptr);

  if(!win_ptr) {
    glfwTerminate();
    return;
  }

  window_.reset(win_ptr);
   
  glfwMakeContextCurrent(window_.get());

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
      ->mouse_move_event(xpos, ypos);
   });

  glfwSetScrollCallback(
   window_.get(), [](GLFWwindow* window, double xoffset, double yoffset) {
     static_cast<application*>(glfwGetWindowUserPointer(window))
      ->mouse_scroll_event(xoffset, yoffset);
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

void application::key_press_event(unsigned char charcode, int mods)
{
  switch(charcode) {
  case 27:
    close_app();
    break;
  case 80: 
  case 112:
    camera.projection_mode(true);
    break;
  case 79:
  case 111:
    camera.projection_mode(false);
    break;
  case 75:
  case 107:
    scene.representation(molphene::molecule_display::spacefill, molecule);
    break;
  case 76:
  case 108:
    scene.representation(molphene::molecule_display::ball_and_stick, molecule);
    break;
  }
}

void application::mouse_press_event(int button, int mods, int pos_x, int pos_y)
{
  click_state.is_down = true;
  click_state.last_x = pos_x;
  click_state.last_y = pos_y;
}

void application::mouse_release_event(int button, int mods, int pos_x, int pos_y)
{
  click_state.is_down = false;
  click_state.last_x = pos_x;
  click_state.last_y = pos_y;
}

void application::mouse_move_event(int pos_x, int pos_y)
{
  if(click_state.is_down) {
    const auto delta_x = static_cast<double>(click_state.last_x) - pos_x;
    const auto delta_y = static_cast<double>(click_state.last_y) - pos_y;

    click_state.last_x = pos_x;
    click_state.last_y = pos_y;

    scene.rotate({M_PI * delta_y / 180, M_PI * delta_x / 180, 0});
  }
}

void application::mouse_scroll_event(int offset_x, int offset_y)
{
  offset_y > 0 ? camera.zoom_in() : camera.zoom_out();
}

void application::framebuffer_size_change_event(int width, int height)
{
  renderer.change_dimension(width, height);
  camera.aspect_ratio(width, height);
  camera.update_view_matrix();
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