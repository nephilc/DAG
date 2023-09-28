set(HDRS Renderer.hpp FrameBuffer.hpp)
set(SRCS Renderer.cpp FrameBuffer.cpp Font.cpp)

add_library(Rendering  STATIC ${HDRS} ${SRCS} )
target_link_libraries(Rendering PUBLIC plog glad objectSystem Assets freetype glm) 
target_include_directories(Rendering PUBLIC .)
