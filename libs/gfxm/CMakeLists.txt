add_library(molphene-gfxm INTERFACE)

target_include_directories(molphene-gfxm
INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)

target_compile_features(molphene-gfxm
  INTERFACE
    cxx_std_17
)

target_compile_options(molphene-gfxm
  INTERFACE
    $<$<CONFIG:Release>:
      -O3
    >
)

