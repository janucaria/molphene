add_library(molphene
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Atom.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Bond.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Chain.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Compound.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Model.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Molecule.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/ColorLightBuffer.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/ColorLightShader.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/ColourManager.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/GlRenderer.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/QuadShader.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/Scene.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/SpacefillRepresentation.cpp"
)

if(APPLE)
  target_link_libraries(molphene PRIVATE "-framework OpenGL")
endif()

target_include_directories(molphene
PUBLIC
  "${PROJECT_SOURCE_DIR}/third_party/GSL/include"
  "${PROJECT_SOURCE_DIR}/third_party/Gm3d/src"
  "${PROJECT_SOURCE_DIR}/third_party/json/include"
)

target_compile_options(molphene PRIVATE ${MOLPHENE_WARNING_OPTIONS} "-stdlib=libc++")