add_executable(molphene-test
"${PROJECT_SOURCE_DIR}/test/main.cpp"
"${PROJECT_SOURCE_DIR}/test/matrix4.cpp"
"${PROJECT_SOURCE_DIR}/test/vector3.cpp"
"${PROJECT_SOURCE_DIR}/test/color.cpp"
)

find_package(Boost COMPONENTS unit_test_framework)

target_include_directories(molphene-test
PRIVATE
  "${PROJECT_SOURCE_DIR}/src/lib"
)

target_link_libraries(molphene-test PRIVATE libmolphene ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_compile_options(molphene-test PRIVATE ${MOLPHENE_WARNING_OPTIONS} "-stdlib=libc++")
