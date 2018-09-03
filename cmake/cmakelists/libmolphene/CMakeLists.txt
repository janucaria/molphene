add_library(molphene
"${PROJECT_SOURCE_DIR}/src/lib/molphene/m3d/Rgba8.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/m3d/Rgba32f.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Atom.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Bond.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Chain.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Compound.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Model.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Molecule.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/PdbParser.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/ColorLightBuffer.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/ColorLightShader.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/ColourManager.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/Scene.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/SphereMeshBuilder.cpp")

if(NOT EMSCRIPTEN)
  target_link_libraries(molphene PRIVATE "-framework OpenGL")
endif()

target_include_directories(molphene
PUBLIC
  "${PROJECT_SOURCE_DIR}/third_party/GSL/include"
)

target_compile_options(molphene PRIVATE ${MOLPHENE_WARNING_OPTIONS} "-stdlib=libc++")