

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(ProjectMgr SHARED ${SOURCE_FILES})
target_link_libraries(ProjectMgr PUBLIC rapidjson)
target_include_directories(ProjectMgr PUBLIC ./include)

