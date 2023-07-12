
#include "GeometryNode.hpp"

IMPLEMENT_RTTI(GeometryNode, Node)


GeometryNode::GeometryNode(Shader* shader) 
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
    m_shader = shader;
    drawMode = MD_TRI;
}

GeometryNode::GeometryNode():GeometryNode(nullptr)
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
        //glm::mat4 scaleddown = m_world.sc
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


void GeometryNode::save(Stream& stream)
{
    stream.writeln(TYPE.GetName());
    //save model stuff
    Node::save(stream);


}
void GeometryNode::load(Stream& stream)
{
    string typeName = stream.readln();//eading the type line should be in the child loop, so that we create the right kind of node, we assume the type of the root node
    if (typeName != TYPE.GetName()) PLOGE << "Wrong loader, Expected " << TYPE.GetName() << " found in file" << typeName;
    //load model stuff
    Node::load(stream);

}
