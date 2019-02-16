#include <emscripten/bind.h>

#include "application.hpp"

EMSCRIPTEN_BINDINGS(main)
{
  emscripten::class_<molphene::application>("MainApp")
   .constructor<>()
   .function("run", &molphene::application::run)
   .function("openPDBData", &molphene::application::open_pdb_data)
   .function("onCanvasSizeChange",
             &molphene::application::canvas_size_change_callback)
   .function("changeRepresentation",
             &molphene::application::change_representation);
}
