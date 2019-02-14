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


set(Gfxm_TEST_SRC_FILES
"${CMAKE_CURRENT_SOURCE_DIR}/test/matrix3.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/test/matrix4.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/test/rgba_float.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/test/rgba_uint8.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/test/vector2.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/test/vector3.cpp"
)

enable_testing()

foreach(Gfxm_FILES ${Gfxm_TEST_SRC_FILES})

  get_filename_component(Gfxm_NAME ${Gfxm_FILES} NAME_WE)

  set(Gfxm_TARGET_NAME "gfxm-test-${Gfxm_NAME}")

  add_executable(${Gfxm_TARGET_NAME} ${Gfxm_FILES})

  target_link_libraries(${Gfxm_TARGET_NAME} PRIVATE molphene-gfxm Catch2::Catch2)
  target_compile_features(${Gfxm_TARGET_NAME} PUBLIC cxx_std_17)

  add_test(
    NAME ${Gfxm_TARGET_NAME}
    COMMAND ${Gfxm_TARGET_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

endforeach()
