add_executable(molphene-web)

string(JOIN " -s " MOLPHENE_EM_SETTINGS
  DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR
  DYNAMIC_EXECUTION=0
  ENVIRONMENT=web
  EXIT_RUNTIME
  EXPORT_ES6
  EXPORT_NAME=Molphene
  FILESYSTEM=0
  GL_EMULATE_GLES_VERSION_STRING_FORMAT=0
  GL_EXTENSIONS_IN_PREFIXED_FORMAT=0
  GL_POOL_TEMP_BUFFERS=0
  # GL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS=0
  INVOKE_RUN=0
  MALLOC=emmalloc
  MODULARIZE
  RUNNING_JS_OPTS
  STRICT
  SUPPORT_ERRNO=0
  SYSCALLS_REQUIRE_FILESYSTEM=0
  TOTAL_MEMORY=512MB
  USE_CLOSURE_COMPILER
  USE_SDL=0
  "EXTRA_EXPORTED_RUNTIME_METHODS='[\"stringToUTF8\", \"lengthBytesUTF8\"]'"
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
    AGGRESSIVE_VARIABLE_ELIMINATION
    ELIMINATE_DUPLICATE_FUNCTIONS
    NO_ABORTING_MALLOC
    NO_ASSERTIONS
    NO_GL_TRACK_ERRORS
  )
endif()
string(PREPEND MOLPHENE_EM_SETTINGS "-s ")

target_sources(molphene-web
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/application.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

target_link_libraries(molphene-web
  PRIVATE
    GL
    Molphene::molphene
    Molphene::io
    Molphene::app
)

target_link_options(molphene-web
  PRIVATE
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

install(
  TARGETS
    molphene-web
  RUNTIME DESTINATION "./"
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/molphene-web.wasm"
  DESTINATION "./"
)
