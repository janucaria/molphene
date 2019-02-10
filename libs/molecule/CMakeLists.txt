add_library(molphene-molecule
"${CMAKE_CURRENT_SOURCE_DIR}/src/molecule/Atom.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/src/molecule/Bond.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/src/molecule/Chain.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/src/molecule/chemdoodle_json_parser.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/src/molecule/Compound.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/src/molecule/Model.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/src/molecule/Molecule.cpp"
)

target_include_directories(molphene-molecule
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(molphene-molecule
  PUBLIC
    GSL gm3d
  PRIVATE
    nlohmann_json::nlohmann_json 
)

target_compile_features(molphene-molecule
  PRIVATE
    cxx_std_17
)

target_compile_options(molphene-molecule
  PRIVATE
    $<$<CONFIG:Release>:
      -O3
    >
)
