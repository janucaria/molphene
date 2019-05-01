add_executable(molphene-web)

string(JOIN " -s " MOLPHENE_EM_SETTINGS
  DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR
  ENVIRONMENT=web
  EXIT_RUNTIME
  EXPORT_NAME=Molphene
  MALLOC=emmalloc
  MODULARIZE
  NO_DYNAMIC_EXECUTION
  NO_FILESYSTEM
  NO_GL_EMULATE_GLES_VERSION_STRING_FORMAT
  NO_GL_EXTENSIONS_IN_PREFIXED_FORMAT
  NO_GL_POOL_TEMP_BUFFERS
  # NO_GL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS
  NO_INVOKE_RUN
  NO_SYSCALLS_REQUIRE_FILESYSTEM
  NO_USE_SDL
  RUNNING_JS_OPTS
  STRICT
  TOTAL_MEMORY=512MB
  USE_CLOSURE_COMPILER
  "EXTRA_EXPORTED_RUNTIME_METHODS='[\"stringToUTF8\", \"lengthBytesUTF8\"]'"

  NO_SUPPORT_ERRNO
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
