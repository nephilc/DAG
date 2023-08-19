FIND_FILE(GLFW_DLL glfw3.dll PATHS ${CMAKE_CURRENT_SOURCE_DIR})
FIND_FILE(GLFW_LIB glfw.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR})

message("GLFW DLL ${GLFW_DLL}")
message("GLFW LIB ${GLFW_LIB}")

add_library(glfw SHARED IMPORTED GLOBAL)
set_property(TARGET glfw PROPERTY
             IMPORTED_LOCATION ${GLFW_DLL})
set_property(TARGET glfw PROPERTY
             IMPORTED_IMPLIB ${GLFW_LIB})
target_include_directories(glfw INTERFACE .)

