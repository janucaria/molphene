add_library(molphene-io)

add_library(Molphene::io ALIAS molphene-io)

target_sources(molphene-io
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molphene/io/click_state.cpp"
)

target_include_directories(molphene-io
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_features(molphene-io
  PRIVATE
    cxx_std_17
)

target_compile_options(molphene-io
  PRIVATE
    $<$<CONFIG:Release>:
      -O3
    >
)
