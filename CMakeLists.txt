cmake_minimum_required(VERSION 3.11)
project(Molphene)

if(EMSCRIPTEN)
  set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER} CACHE FILEPATH "Compiler")
  set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER} CACHE FILEPATH "Compiler")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

set(MOLPHENE_WARNING_OPTIONS "-Wall" "-Wpedantic")

add_subdirectory("${PROJECT_SOURCE_DIR}/cmake/cmakelists/libmolphene")
add_subdirectory("${PROJECT_SOURCE_DIR}/cmake/cmakelists/molphene")
add_subdirectory("${PROJECT_SOURCE_DIR}/cmake/cmakelists/molphene-test")
add_subdirectory("${PROJECT_SOURCE_DIR}/cmake/cmakelists/molphene-web")

