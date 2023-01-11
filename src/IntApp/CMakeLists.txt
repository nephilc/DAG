#add_subdirectory(src)
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(IntApp ${SOURCE_FILES})
target_include_directories(IntApp PUBLIC ./include)
target_link_libraries(
  IntApp
  myInterpreter
)
