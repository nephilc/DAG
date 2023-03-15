#include<ModelNode.hpp>

IMPLEMENT_RTTI(ModelNode, GeometryNode)

ModelNode::ModelNode():  ModelNode(nullptr)
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
   
}

ModelNode::ModelNode(Model *model): m_model(model)
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here

}

void ModelNode::Draw(Camera *camera, float deltaTime)
{
    if(m_model!=nullptr) GeometryDraw(camera, deltaTime);
    Node::Draw(camera, deltaTime);
}

void ModelNode::GeometryDraw(Camera *camera, float deltaTime)
{
    if(m_shader!=nullptr)
    {
        GeometryNode::GeometryDraw(camera, deltaTime);
        m_model->Draw(m_shader);
    }
}

void ModelNode::setModel(Model *model)
{
    m_model = model;
}

Model*  ModelNode::getModel()
{
    return m_model;
}
ModelNode::~ModelNode()
{
}
