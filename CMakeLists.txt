cmake_minimum_required(VERSION 3.13)
project(Molphene)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory("third_party/GSL")
add_subdirectory("third_party/json")
add_subdirectory("third_party/Catch2")

enable_testing()

if(EMSCRIPTEN)
  set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER} CACHE FILEPATH "Compiler")
  set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER} CACHE FILEPATH "Compiler")
  
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(Boost)

if(NOT Boost_FOUND)
  add_library(Boost::boost INTERFACE IMPORTED)
  if(BOOST_ROOT)
    target_include_directories(Boost::boost INTERFACE ${BOOST_ROOT}/include)
  elseif(BOOST_INCLUDEDIR)
    target_include_directories(Boost::boost INTERFACE ${BOOST_INCLUDEDIR})
  else()
    message(SEND_ERROR "Unable to find the Boost header files. Please set BOOST_ROOT to the root directory containing Boost or BOOST_INCLUDEDIR to the directory containing Boost's headers.")
  endif()
endif()

if(APPLE)
  add_compile_definitions(GL_SILENCE_DEPRECATION)
endif()

add_compile_options(-Wall -Wpedantic -pedantic-errors -fno-rtti)

add_subdirectory("libs/gfxm")
add_subdirectory("libs/molecule")
add_subdirectory("libs/core")
add_subdirectory("cmake/cmakelists/molphene-glfw")

if(EMSCRIPTEN)
  add_subdirectory("cmake/cmakelists/molphene-web")
endif()

