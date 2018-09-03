#include <emscripten/bind.h>
#include "Application.hpp"

EMSCRIPTEN_BINDINGS(main)
{
  emscripten::class_<molphene::Application>("MainApp")
	.constructor<>()
	.function("run", &molphene::Application::run)
	.function("openPDBData", &molphene::Application::open_pdb_data)
	.function("onCanvasSizeChange", &molphene::Application::canvas_size_change_callback);
}
