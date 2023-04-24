set(HDRS  Object.hpp  Object.inl RTTI.hpp Stream.hpp)
#RTTI.hpp RTTI.inl RTTIMCR.h
set(SRCS Object.cpp  RTTI.cpp Stream.cpp)
#RTTI.cpp
add_library(objectSystem STATIC ${HDRS} ${SRCS} ) 
target_include_directories(objectSystem PUBLIC .)
target_link_libraries(objectSystem PUBLIC  plog)
