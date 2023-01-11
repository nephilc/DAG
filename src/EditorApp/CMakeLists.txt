#add_subdirectory(src)
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(EDITOR ${SOURCE_FILES})
target_include_directories(EDITOR PUBLIC ./include)
target_link_libraries(
	EDITOR PRIVATE
  plog 
  imgui
  glfw
  stb_image
  glad
  )
