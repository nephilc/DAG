add_library(assimp SHARED IMPORTED GLOBAL)


#apparently it needs the full path, or the binary should be moven next to the executable
set_target_properties(assimp PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/${ANDROID_ABI}/libassimp.so)

message("${CMAKE_CURRENT_SOURCE_DIR}/${ANDROID_ABI}ANDORIDASSIMP")
target_include_directories(assimp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}   ${CMAKE_CURRENT_SOURCE_DIR}/${ANDROID_ABI})
