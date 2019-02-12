cmake_minimum_required(VERSION 3.13)
project(Molphene)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory("third_party/GSL")
add_subdirectory("third_party/json")

enable_testing()

if(EMSCRIPTEN)
  set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER} CACHE FILEPATH "Compiler")
  set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER} CACHE FILEPATH "Compiler")
  
  set(CMAKE_CXX_STANDARD 17)
endif()

if(APPLE)
  add_compile_definitions(GL_SILENCE_DEPRECATION)
endif()

find_package(Boost)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIR})
elseif(BOOST_ROOT)
  include_directories("${BOOST_ROOT}/include")
elseif(BOOST_INCLUDEDIR)
  include_directories(${BOOST_INCLUDEDIR})
else()
  message(SEND_ERROR "Unable to find the Boost header files. Please set BOOST_ROOT to the root directory containing Boost or BOOST_INCLUDEDIR to the directory containing Boost's headers.")
endif()

add_compile_options(-Wall -Wpedantic -pedantic-errors -fno-rtti)

add_subdirectory("libs/gfxm")
add_subdirectory("libs/molecule")
add_subdirectory("cmake/cmakelists/libmolphene")
add_subdirectory("cmake/cmakelists/molphene-glfw")

if(EMSCRIPTEN)
  add_subdirectory("cmake/cmakelists/molphene-web")
endif()

