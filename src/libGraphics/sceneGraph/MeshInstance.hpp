#ifndef MESHINSTANCE_HPP
#define MESHINSTANCE_HPP
#include"Node.hpp"
#include "Mesh.hpp"

//so a node may contain zero or many meshes

class MeshInstance : public Node
{
private:
    /* data */
    Mesh* m_meshData;

    //if child node is mesh, then draw
public:
    MeshInstance();
    MeshInstance(Mesh* meshData);
    ~MeshInstance();
    void Draw();
};

#endif