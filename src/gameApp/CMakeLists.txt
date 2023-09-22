#add_subdirectory(src)
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )

add_library(GameAPP STATIC ${SOURCE_FILES})
target_include_directories(GameAPP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/DefaultActions" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"  )
target_link_libraries(
	GameAPP PUBLIC
  plog 
  imgui
  glfw
  stb_image
  glad
  Assets Graphics backend objectSystem
  )
