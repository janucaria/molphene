add_library(molphene-gfxm INTERFACE)

add_library(Molphene::gfxm ALIAS molphene-gfxm)

target_include_directories(molphene-gfxm
INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)

target_compile_options(molphene-gfxm
  INTERFACE
    $<$<CONFIG:Release>:
      -O3
    >
)

target_link_libraries(molphene-gfxm
  INTERFACE
    Cppid::gm3d
)
