add_subdirectory(rendering)
add_subdirectory(sceneGraph)
add_subdirectory(shaders)
add_subdirectory(objectSystem)

add_library(Graphics INTERFACE)

target_link_libraries(Graphics INTERFACE sceneGraph Rendering shaders objectSystem)
