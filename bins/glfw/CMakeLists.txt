
add_executable(molphene-glfw)

target_sources(molphene-glfw
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

target_link_libraries(molphene-glfw
  PRIVATE
    Molphene::molphene
)

if(EMSCRIPTEN)

  set_target_properties(molphene-glfw PROPERTIES SUFFIX ".html")
  set_target_properties(molphene-glfw PROPERTIES LINK_FLAGS "-s TOTAL_MEMORY=512MB -s USE_GLFW=3 -O0")

else()

  find_package(glfw3 REQUIRED)
  target_link_libraries(molphene-glfw PRIVATE glfw)

  if(APPLE)
    target_link_libraries(molphene-glfw PRIVATE "-framework CoreVideo" "-framework IOKit" "-framework Cocoa")
  endif()

endif()
