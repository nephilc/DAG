set(HDRS Model/Mesh.hpp Camera.hpp Model/Model.hpp MeshInstance.hpp Node.hpp  animData.h assimp_glm_helpers.h animator.h WorldNode.hpp SceneElements.hpp ModelNode.hpp ScreenCanvas.hpp NDCsquare.hpp)
set(SRCS Model/Mesh.cpp Model/Model.cpp MeshInstance.cpp Node.cpp AnimatedNode.cpp WorldNode.cpp ModelNode.cpp GeometryNode.cpp ScreenCanvas.cpp NDCsquare.cpp)
#Model1.cpp Model1.hpp
add_library(sceneGraph STATIC ${HDRS} ${SRCS} "Model/StaticMesh.cpp" "Model/StaticModel.cpp" "animation.cpp") 
target_include_directories(sceneGraph PUBLIC . ./Model)
target_link_libraries(sceneGraph PUBLIC glm plog  shaders stb_image objectSystem assimp  backend Rendering Assets)




#model_anmiation includes  animData and assimp_glm_helpers

#Animator includes animation and bone

#bone includes helper

#animation includes model and anim data and bone
