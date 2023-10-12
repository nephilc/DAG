if(UNIX AND NOT ANDROID)
add_subdirectory(linux)
elseif(ANDROID)
add_subdirectory(android)
elseif(WIN32)
add_subdirectory(windows)
endif()

