
#include "GeometryNode.hpp"

IMPLEMENT_RTTI(GeometryNode, Node)


GeometryNode::GeometryNode(Shader* shader) 
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
    m_shader = shader;
    drawMode = MD_TRI;
}

GeometryNode::GeometryNode()
{
}

GeometryNode::~GeometryNode()
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here

}

void GeometryNode::Draw(Camera* camera, float deltaTime) 
{
    Node::Draw(camera, deltaTime);
}
//only call this in child methods
void GeometryNode::GeometryDraw(Camera *camera, float deltaTime)
{
        m_shader->use();
        m_shader->setMat4("projection", Node::projection);
        m_shader->setMat4("view", camera->GetViewMatrix());
        m_shader->setMat4("model", m_world);
    
}

void GeometryNode::setShader(Shader* shader)
{
    m_shader = shader;
}    

Shader* GeometryNode::getShader()
{
    return m_shader;
}    

