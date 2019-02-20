add_library(molphene-app INTERFACE)

add_library(Molphene::app ALIAS molphene-app)

target_include_directories(molphene-app
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_options(molphene-app
  INTERFACE
    $<$<CONFIG:Release>:
      -O3
    >
)
