cmake_minimum_required(VERSION 3.13)
project(Molphene)

add_subdirectory("third_party/Gm3d" EXCLUDE_FROM_ALL)

find_package(OpenGL MODULE REQUIRED COMPONENTS OpenGL)
find_package(Boost CONFIG 1.73 REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)

if(EMSCRIPTEN)
  list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/tools/cmake")

  find_package(nlohmann_json 3.7 MODULE REQUIRED)
else()
  find_package(glfw3 CONFIG 3.3 REQUIRED)
  find_package(glad CONFIG 0.1 REQUIRED)
  find_package(nlohmann_json 3.7 CONFIG REQUIRED)
endif()

add_compile_options(-Wall -Wpedantic -pedantic-errors)

add_subdirectory("libs/gfxm")
add_subdirectory("libs/molecule")
add_subdirectory("libs/core")
add_subdirectory("libs/io")

add_subdirectory("bins/app")
add_subdirectory("bins/glfw")
if(EMSCRIPTEN)
  add_subdirectory("bins/web")
endif()

