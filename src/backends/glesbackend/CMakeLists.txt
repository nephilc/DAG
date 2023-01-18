#cmake_minimum_required(VERSION 3.14)
#project(EDITOR VERSION 1.0)


#set(CMAKE_CXX_STANDARD 14)
#configure_file(Config.h.in Config.h)

add_library(glbackend SHARED backend.hpp backend.cpp backendInterface)
target_link_libraries(glbackend PRIVATE  GLESv3 glm)
target_include_directories(glbackend PUBLIC .  )

#adapt every backend to the interface used by the engine
#the engine wouldn't know the difference.
