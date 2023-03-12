set(HDRS Renderer.hpp FrameBuffer.hpp)
set(SRCS Renderer.cpp FrameBuffer.cpp)

add_library(Rendering  STATIC ${HDRS} ${SRCS})
target_link_libraries(Rendering PUBLIC plog glad objectSystem) 
target_include_directories(Rendering PUBLIC .)