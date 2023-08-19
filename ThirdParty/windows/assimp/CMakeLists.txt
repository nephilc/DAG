FIND_FILE(ASSIMP_DLL assimp-vc143-mt.dll PATHS ${CMAKE_CURRENT_SOURCE_DIR})
FIND_FILE(ASSIMP_LIB assimp-vc143-mt.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR})

message("ASSIMP DLL ${ASSIMP_DLL}")
message("ASSIMP LIB ${ASSIMP_LIB}")

add_library(assimp SHARED IMPORTED GLOBAL)
set_property(TARGET assimp PROPERTY
             IMPORTED_LOCATION ${ASSIMP_DLL})
set_property(TARGET assimp PROPERTY
             IMPORTED_IMPLIB ${ASSIMP_LIB})
target_include_directories(assimp INTERFACE .)
