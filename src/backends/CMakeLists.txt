add_subdirectory(backend)

#cross compilation
if(ANDROID_MODULES)
add_subdirectory(glesbackend)
add_library(backend ALIAS glesbackend)
else()
add_subdirectory(glbackend)
add_library(backend ALIAS glbackend)
endif()

