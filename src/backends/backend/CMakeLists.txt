
add_library(backendInterface SHARED backend.hpp backend.cpp)
target_link_libraries(backendInterface PRIVATE  glm)
target_include_directories(backendInterface PUBLIC .)

