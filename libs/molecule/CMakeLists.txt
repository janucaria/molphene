add_library(molphene-molecule)

add_library(Molphene::molecule ALIAS molphene-molecule)

target_sources(molphene-molecule
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molecule/atom.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molecule/bond.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molecule/chemdoodle_json_parser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/molecule/molecule.cpp"
)

target_include_directories(molphene-molecule
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(molphene-molecule
  PUBLIC
    GSL Molphene::gfxm
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

target_link_libraries(molphene-molecule PRIVATE Boost::boost)