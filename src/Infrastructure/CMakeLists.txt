

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(Infrastructure SHARED ${SOURCE_FILES})
#target_link_libraries(Graph PUBLIC test)
target_include_directories(Infrastructure PUBLIC ./include)

