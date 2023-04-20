set(SRCS AssetManager.cpp)
set(HDRS AssetManager.hpp)

add_library(Assets STATIC ${SRCS} ${HDRS} "Action.cpp")
target_link_libraries(Assets PUBLIC plog assimp Graphics objectSystem)
target_include_directories(Assets PUBLIC .)