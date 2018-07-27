cmake_minimum_required(VERSION 3.11)
project(Molphene)

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

set(MOLPHENE_SRC_FILES
"${PROJECT_SOURCE_DIR}/src/m3d/Rgba8.cpp"
"${PROJECT_SOURCE_DIR}/src/m3d/Rgba32f.cpp"
"${PROJECT_SOURCE_DIR}/src/mol/Atom.cpp"
"${PROJECT_SOURCE_DIR}/src/mol/Bond.cpp"
"${PROJECT_SOURCE_DIR}/src/mol/Chain.cpp"
"${PROJECT_SOURCE_DIR}/src/mol/Compound.cpp"
"${PROJECT_SOURCE_DIR}/src/mol/Model.cpp"
"${PROJECT_SOURCE_DIR}/src/mol/Molecule.cpp"
"${PROJECT_SOURCE_DIR}/src/mol/Pdb_parser.cpp"
"${PROJECT_SOURCE_DIR}/src/Camera.cpp"
"${PROJECT_SOURCE_DIR}/src/color_light_buffer.cpp"
"${PROJECT_SOURCE_DIR}/src/Color_light_shader.cpp"
"${PROJECT_SOURCE_DIR}/src/Colour_manager.cpp"
"${PROJECT_SOURCE_DIR}/src/Scene.cpp"
"${PROJECT_SOURCE_DIR}/src/sphere_data.cpp")

find_package(glfw3 REQUIRED)

add_executable(molphene
  ${MOLPHENE_SRC_FILES}
  "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

target_link_libraries(molphene PRIVATE glfw "-framework CoreVideo" "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

target_compile_options(molphene PRIVATE "-Wall" "-stdlib=libc++")

target_include_directories(molphene
PRIVATE
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/src"
)
