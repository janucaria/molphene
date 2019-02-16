add_library(molphene)

target_sources(molphene
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src/lib/molphene/ballstick_representation.cpp"
    "${PROJECT_SOURCE_DIR}/src/lib/molphene/color_light_buffer.cpp"
    "${PROJECT_SOURCE_DIR}/src/lib/molphene/color_light_shader.cpp"
    "${PROJECT_SOURCE_DIR}/src/lib/molphene/color_manager.cpp"
    "${PROJECT_SOURCE_DIR}/src/lib/molphene/gl_renderer.cpp"
    "${PROJECT_SOURCE_DIR}/src/lib/molphene/quad_shader.cpp"
    "${PROJECT_SOURCE_DIR}/src/lib/molphene/scene.cpp"
    "${PROJECT_SOURCE_DIR}/src/lib/molphene/spacefill_representation.cpp"
)

target_include_directories(molphene
  PUBLIC
    "${PROJECT_SOURCE_DIR}/src/lib"
)

target_link_libraries(molphene
  PUBLIC
    molphene-gfxm
    molphene-molecule
    GSL 
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

if(APPLE)
  target_link_libraries(molphene PRIVATE "-framework OpenGL")
endif()