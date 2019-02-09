add_library(molphene
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Atom.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Bond.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Chain.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Compound.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Model.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/mol/Molecule.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/BallStickRepresentation.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/ColorLightBuffer.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/ColorLightShader.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/ColourManager.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/GlRenderer.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/QuadShader.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/Scene.cpp"
"${PROJECT_SOURCE_DIR}/src/lib/molphene/SpacefillRepresentation.cpp"
)

target_include_directories(molphene
  INTERFACE
    "${PROJECT_SOURCE_DIR}/src/lib"
)

target_link_libraries(molphene PUBLIC GSL nlohmann_json::nlohmann_json gm3d)
target_compile_features(molphene PUBLIC cxx_std_17)

if(APPLE)
  target_link_libraries(molphene PRIVATE "-framework OpenGL")
endif()