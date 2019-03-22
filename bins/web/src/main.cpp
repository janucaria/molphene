#include "application.hpp"

#include <cstdlib>
#include <memory>

inline auto app = molphene::application{};

struct malloc_guard {
  template<typename T>
  void operator()(T* ptr) const noexcept
  {
    std::free(ptr);
  }
};

extern "C" {

EMSCRIPTEN_KEEPALIVE
void molphene_application_setup()
{
  app.setup();
}

EMSCRIPTEN_KEEPALIVE
void molphene_application_open_pdb_data(char* pdbdata)
{
  auto _ = std::unique_ptr<char, malloc_guard>{pdbdata};
  app.open_pdb_data(pdbdata);
}

EMSCRIPTEN_KEEPALIVE
void molphene_application_canvas_size_changed(int width, int height)
{
  app.canvas_size_change_callback(width, height);
}

EMSCRIPTEN_KEEPALIVE
void molphene_application_change_representation(int representation_type)
{
  app.change_representation(representation_type);
}

EMSCRIPTEN_KEEPALIVE
void molphene_application_render_frame()
{
  app.render_frame();
}
}
