
add_executable(molphene
"${PROJECT_SOURCE_DIR}/src/bin/glfw/main.cpp"
)
target_include_directories(molphene
PRIVATE
"${PROJECT_SOURCE_DIR}/src/lib"
)
target_link_libraries(molphene PRIVATE libmolphene)

if(EMSCRIPTEN)

set_target_properties(molphene PROPERTIES SUFFIX ".html")
set_target_properties(molphene PROPERTIES LINK_FLAGS "-s TOTAL_MEMORY=512MB -s USE_GLFW=3 -O0")

else()
find_package(glfw3 REQUIRED)

target_link_libraries(molphene PRIVATE glfw "-framework CoreVideo" "-framework IOKit" "-framework Cocoa")

target_compile_options(molphene PRIVATE "-Wall" "-stdlib=libc++")

endif()
