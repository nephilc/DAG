

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(Interpreter SHARED ${SOURCE_FILES})
target_link_libraries(Interpreter PUBLIC Infrastructure)
target_include_directories(Interpreter PUBLIC ./include)

