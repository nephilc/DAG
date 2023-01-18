#include "MeshInstance.hpp"
#include <plog/Log.h> 



MeshInstance::MeshInstance()
{
    PLOGE<<"calling MESHINSTANCE CONSTRUCTOR";
    type = MESH;

}

MeshInstance::MeshInstance(Mesh* meshData) : m_meshData(meshData)
{
    PLOGE<<"calling MESHINSTANCE CONSTRUCTOR SETTING MESHDATA";
    type = MESH;

}

MeshInstance::~MeshInstance()
{
    PLOGE<<"CALLING MESHINSTANCE DESTRUCTOR";

}

void MeshInstance::Draw()
{

}
