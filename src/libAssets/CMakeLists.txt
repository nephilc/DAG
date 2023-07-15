#set(SRCS AssetManager.cpp Action.cpp KeyMap.cpp)
file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )
set(HDRS AssetManager.hpp Action.hpp KeyMap.hpp)

add_library(Assets STATIC ${SRCS} ${HDRS} )
target_link_libraries(Assets PUBLIC plog assimp Graphics objectSystem)
target_include_directories(Assets PUBLIC .)