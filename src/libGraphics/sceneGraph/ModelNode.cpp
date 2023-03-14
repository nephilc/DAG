#include<ModelNode.hpp>

IMPLEMENT_RTTI(ModelNode, Node)

ModelNode::ModelNode()
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here

}

ModelNode::ModelNode(Model *model): m_model(model)
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here

}

void ModelNode::Draw(Camera *camera, float deltaTime)
{
    Node::Draw(camera, deltaTime);
}

ModelNode::~ModelNode()
{
}
