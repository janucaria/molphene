
add_executable(molphene-glfw)

target_sources(molphene-glfw
  PRIVATE
    src/application.cpp
    src/main.cpp
)

target_link_libraries(molphene-glfw
  PRIVATE
    Molphene::molphene
    Molphene::io
    Molphene::app
)

if(EMSCRIPTEN)

  set_target_properties(molphene-glfw PROPERTIES SUFFIX ".html")
  set_target_properties(molphene-glfw PROPERTIES LINK_FLAGS "-s TOTAL_MEMORY=512MB -s USE_GLFW=3 -O0")

else()

  target_link_libraries(molphene-glfw
    PRIVATE
      ${CMAKE_DL_LIBS}
      glfw
      glad::glad
  )

endif()
