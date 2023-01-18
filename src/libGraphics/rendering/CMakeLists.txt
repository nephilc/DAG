set(HDRS Renderer.hpp)
set(SRCS Renderer.cpp)

add_library(Rendering  SHARED ${HDRS} ${SRCS}) 
target_include_directories(Rendering PUBLIC .)