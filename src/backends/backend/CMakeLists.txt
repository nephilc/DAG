
add_library(backendInterface STATIC backend.hpp backend.cpp)
target_link_libraries(backendInterface PRIVATE  glm)
target_include_directories(backendInterface PUBLIC .)

