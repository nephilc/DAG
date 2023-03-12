set(HDRS Model/Mesh.hpp Camera.hpp Model/Model.hpp MeshInstance.hpp Node.hpp  animData.h assimp_glm_helpers.h animator.h WorldNode.hpp SceneElements.hpp)
set(SRCS Model/Mesh.cpp Model/Model.cpp MeshInstance.cpp Node.cpp AnimatedNode.cpp WorldNode.cpp)
#Model1.cpp Model1.hpp
add_library(sceneGraph STATIC ${HDRS} ${SRCS}) 
target_include_directories(sceneGraph PUBLIC . ./Model)
target_link_libraries(sceneGraph PUBLIC glm plog  shaders stb_image objectSystem assimp  backend)




#model_anmiation includes  animData and assimp_glm_helpers

#Animator includes animation and bone

#bone includes helper

#animation includes model and anim data and bone
