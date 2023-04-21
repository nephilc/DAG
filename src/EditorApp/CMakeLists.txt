#add_subdirectory(src)
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )

add_executable(EDITORAPP ${SOURCE_FILES}  )
target_include_directories(EDITORAPP PUBLIC . )
target_link_libraries(
	EDITORAPP PRIVATE
	EDITOR
  plog 
  imgui
  glfw
  stb_image
  glad
  )
  
set_target_properties( EDITORAPP
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/EditorBin"
)

