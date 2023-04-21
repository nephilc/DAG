#add_subdirectory(src)
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Actions/*.cpp")

add_library(EDITOR STATIC ${SOURCE_FILES})
target_include_directories(EDITOR PUBLIC ./include "./Actions")
target_link_libraries(
	EDITOR PUBLIC
  plog 
  imgui
  glfw
  stb_image
  glad
  Assets Graphics backend objectSystem
  )
