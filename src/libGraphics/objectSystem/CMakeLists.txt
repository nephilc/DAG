set(HDRS  Object.hpp  Object.inl )
#RTTI.hpp RTTI.inl RTTIMCR.h
set(SRCS Object.cpp  )
#RTTI.cpp
add_library(objectSystem SHARED ${HDRS} ${SRCS}) 
target_include_directories(objectSystem PUBLIC .)
target_link_libraries(objectSystem PUBLIC  plog)