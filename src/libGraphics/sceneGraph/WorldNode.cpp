#include<WorldNode.hpp>
#include<backend.hpp>
IMPLEMENT_RTTI(WorldNode, Node)
WorldNode::WorldNode(float r, float g, float b, float a)
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here

    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
}

void WorldNode::Draw(Camera *camera, float deltaTime)
{
    backend::getBackend()->clearColorAndBuffersDC(clearColor[0], clearColor[1], clearColor[2], clearColor[4]);
    Node::Draw(camera, deltaTime);

}

void WorldNode::setClearColor(float r, float g, float b, float a)
{
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;

}

WorldNode::~WorldNode()
{
}