

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(myInterpreter SHARED ${SOURCE_FILES})
target_link_libraries(myInterpreter PUBLIC Infrastructure)
target_include_directories(myInterpreter PUBLIC ./include)

