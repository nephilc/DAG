set(SRCS AssetManager.cpp)
set(HDRS AssetManager.hpp)

add_library(Assets ${SRCS} ${HDRS})
target_link_libraries(Assets PUBLIC plog assimp Graphics )
target_include_directories(Assets PUBLIC .)