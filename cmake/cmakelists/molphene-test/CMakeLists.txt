set(Molphene_TEST_SRC_FILES
"${PROJECT_SOURCE_DIR}/test/color.cpp"
"${PROJECT_SOURCE_DIR}/test/vector3.cpp"
"${PROJECT_SOURCE_DIR}/test/matrix4.cpp"
)

foreach(Molphene_FILES ${Molphene_TEST_SRC_FILES})

  get_filename_component(Molphene_NAME ${Molphene_FILES} NAME_WE)

  set(Molphene_TARGET_NAME "molphene-test-${Molphene_NAME}")

  add_executable(${Molphene_TARGET_NAME} ${Molphene_FILES})

  target_link_libraries(${Molphene_TARGET_NAME} PRIVATE molphene)

  target_include_directories(${Molphene_TARGET_NAME}
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src/lib"
    "${PROJECT_SOURCE_DIR}/third_party/Catch2/single_include"
  )

  target_compile_options(${Molphene_TARGET_NAME} PRIVATE ${MOLPHENE_WARNING_OPTIONS} "-stdlib=libc++")

  add_test(
    NAME ${Molphene_TARGET_NAME}
    COMMAND ${Molphene_TARGET_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

endforeach()
