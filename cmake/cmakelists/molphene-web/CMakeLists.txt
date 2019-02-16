add_executable(molphene-web)

string(JOIN " -s " MOLPHENE_EM_SETTINGS
  ENVIRONMENT=web
  EXPORT_NAME=Molphene
  MODULARIZE
  NO_DYNAMIC_EXECUTION
  NO_FILESYSTEM
  NO_USE_SDL
  TOTAL_MEMORY=512MB
  STRICT
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  string(JOIN " -s " MOLPHENE_EM_SETTINGS
    ${MOLPHENE_EM_SETTINGS}
    GL_ASSERTIONS
    GL_DEBUG
  )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  string(JOIN " -s " MOLPHENE_EM_SETTINGS
    ${MOLPHENE_EM_SETTINGS}
    ELIMINATE_DUPLICATE_FUNCTIONS
    NO_ASSERTIONS
  )
endif()
string(PREPEND MOLPHENE_EM_SETTINGS "-s ")

target_sources(molphene-web
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src/bin/web/application.cpp"
    "${PROJECT_SOURCE_DIR}/src/bin/web/click_state.cpp"
    "${PROJECT_SOURCE_DIR}/src/bin/web/embind-MainApp.cpp"
)

target_link_libraries(molphene-web
  PRIVATE
    GL
    molphene
)

target_compile_options(molphene-web
  PRIVATE
    -frtti
)

target_link_options(molphene-web
  PRIVATE
    --bind
    $<$<CONFIG:Debug>:
      -O0 -g4
      --source-map-base ./
    >
    $<$<CONFIG:Release>:
      -O3
    >
)

set_target_properties(molphene-web
  PROPERTIES
    SUFFIX ".js"
    LINK_FLAGS ${MOLPHENE_EM_SETTINGS}
)
