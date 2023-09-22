#add_subdirectory(src)
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )

add_executable(GameEXE ${SOURCE_FILES}  )
target_include_directories(GameEXE PUBLIC . )
target_link_libraries(
	GameEXE PRIVATE
	GameAPP
  plog 
  imgui
  glfw
  stb_image
  glad
  )
  
set_target_properties( GameEXE
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/GameBin"
)

