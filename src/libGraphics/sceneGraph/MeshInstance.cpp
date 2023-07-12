#include "MeshInstance.hpp"
#include <plog/Log.h> 



MeshInstance::MeshInstance()
{
    PLOGI<<"calling MESHINSTANCE CONSTRUCTOR";
    type = MESH;

}

MeshInstance::MeshInstance(Mesh* meshData) : m_meshData(meshData)
{
    PLOGI<<"calling MESHINSTANCE CONSTRUCTOR SETTING MESHDATA";
    type = MESH;

}

MeshInstance::~MeshInstance()
{
    PLOGI<<"CALLING MESHINSTANCE DESTRUCTOR";

}

void MeshInstance::Draw()
{

}
