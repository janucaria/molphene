#include <emscripten/bind.h>

#include "application.hpp"

EMSCRIPTEN_BINDINGS(main)
{
  using base_application_t = molphene::basic_application<molphene::application>;
  emscripten::class_<base_application_t>("BaseApp")
   .function("setup", &base_application_t::setup)
   .function("openPDBData", &base_application_t::open_pdb_data)
   .function("onCanvasSizeChange",
             &base_application_t::canvas_size_change_callback)
   .function("changeRepresentation", &base_application_t::change_representation)
   .function("renderFrame", &base_application_t::render_frame);

  emscripten::class_<molphene::application,
                     emscripten::base<base_application_t>>("MainApp")
   .constructor<>();
}
