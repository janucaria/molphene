include(FindPackageHandleStandardArgs)

find_path(nlohmann_json_INCLUDE_DIR nlohmann)

find_package_handle_standard_args(nlohmann_json DEFAULT_MSG
  nlohmann_json_INCLUDE_DIR
)

add_library(nlohmann_json::nlohmann_json INTERFACE IMPORTED)

target_include_directories(nlohmann_json::nlohmann_json
  INTERFACE
    ${nlohmann_json_INCLUDE_DIR})
