add_library(molphene)

add_library(Molphene::molphene ALIAS molphene)

target_sources(molphene
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/color_light_shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/color_manager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/gl_renderer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/quad_shader.cpp"
)

target_compile_definitions(molphene
  PRIVATE
    GL_GLEXT_PROTOTYPES
)

target_include_directories(molphene
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(molphene
  PUBLIC
    Molphene::gfxm
    Molphene::molecule
    Microsoft.GSL::GSL
    Boost::boost
)

target_compile_features(molphene
  PUBLIC
    cxx_std_17
)

target_compile_options(molphene
  PUBLIC
    $<$<CONFIG:Release>:
      -O3
    >
)
