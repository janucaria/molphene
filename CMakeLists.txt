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
"${PROJECT_SOURCE_DIR}/src/mol/PdbParser.cpp"
"${PROJECT_SOURCE_DIR}/src/ColorLightBuffer.cpp"
"${PROJECT_SOURCE_DIR}/src/ColorLightShader.cpp"
"${PROJECT_SOURCE_DIR}/src/ColourManager.cpp"
"${PROJECT_SOURCE_DIR}/src/Scene.cpp"
"${PROJECT_SOURCE_DIR}/src/SphereMeshBuilder.cpp")

add_executable(molphene
  ${MOLPHENE_SRC_FILES}
  "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

if(EMSCRIPTEN)
  set_target_properties(molphene PROPERTIES SUFFIX ".html")
  set_target_properties(molphene PROPERTIES LINK_FLAGS "-s \"EXTRA_EXPORTED_RUNTIME_METHODS=['stringToUTF8','lengthBytesUTF8']\" -s TOTAL_MEMORY=512MB -s USE_GLFW=3 -O0")

else()
  find_package(glfw3 REQUIRED)

  target_link_libraries(molphene PRIVATE glfw "-framework CoreVideo" "-framework IOKit" "-framework Cocoa" "-framework OpenGL")

  target_compile_options(molphene PRIVATE "-Wall" "-stdlib=libc++")

endif()

target_include_directories(molphene
PRIVATE
  "/usr/local/include"
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/src"
)


find_package(Boost COMPONENTS unit_test_framework)

add_executable(molphene_test
"${PROJECT_SOURCE_DIR}/test/main.cpp"
"${PROJECT_SOURCE_DIR}/test/matrix4.cpp"
"${PROJECT_SOURCE_DIR}/test/vector3.cpp"
"${PROJECT_SOURCE_DIR}/test/color.cpp"
)

target_include_directories(molphene_test
PRIVATE
  "/usr/local/include"
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/src"
)

target_link_libraries(molphene_test PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

target_compile_options(molphene_test PRIVATE "-Wall" "-stdlib=libc++")
