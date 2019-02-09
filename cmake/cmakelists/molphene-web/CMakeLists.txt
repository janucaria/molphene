add_executable(molphene-web
  "${PROJECT_SOURCE_DIR}/src/bin/web/Application.cpp"
  "${PROJECT_SOURCE_DIR}/src/bin/web/ClickState.cpp"
  "${PROJECT_SOURCE_DIR}/src/bin/web/embind-MainApp.cpp"
)

target_link_libraries(molphene-web PRIVATE molphene)

string(JOIN " -s " MOLPHENE_EM_SETTINGS
"GL_ASSERTIONS=1"
"GL_DEBUG=1"
"TOTAL_MEMORY=512MB"
"USE_GLFW=0"
"USE_SDL=0"
"MODULARIZE=1"
)

string(JOIN " " MOLPHENE_EM_OPTIONS
"-O0 -g4"
"--source-map-base ./"
"--bind"
"-s ${MOLPHENE_EM_SETTINGS}"
)

set_target_properties(molphene-web PROPERTIES SUFFIX ".js")
set_target_properties(molphene-web PROPERTIES LINK_FLAGS ${MOLPHENE_EM_OPTIONS})
