set(HDRS Shader.hpp)
set(SRCS Shader.cpp)

add_library(shaders STATIC ${HDRS} ${SRCS}) 
target_include_directories(shaders PUBLIC .)
#shader no longer depends on glad
target_link_libraries(shaders PUBLIC glm plog  objectSystem backend)