add_library(molphene)

add_library(Molphene::molphene ALIAS molphene)

target_sources(molphene
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/ballstick_representation.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/color_light_shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/color_manager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/gl_renderer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/quad_shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/spacefill_representation.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/spacefill_instance_representation.cpp"
)

target_include_directories(molphene
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(molphene
  PUBLIC
    Molphene::gfxm
    Molphene::molecule
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