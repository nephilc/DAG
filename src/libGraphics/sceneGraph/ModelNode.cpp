#include<ModelNode.hpp>
#include<AssetManager.hpp>
IMPLEMENT_RTTI(ModelNode, GeometryNode)

ModelNode::ModelNode():  GeometryNode(nullptr), m_model(nullptr)
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here

   
}

ModelNode::ModelNode(Model *model): m_model(model), GeometryNode(nullptr)
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
    
  

}

void ModelNode::Draw(Camera *camera, float deltaTime)
{
    if (m_model != nullptr) {
        GeometryDraw(camera, deltaTime);
        Node::Draw(camera, deltaTime);
    }
}

void ModelNode::GeometryDraw(Camera *camera, float deltaTime)
{
    if(m_shader!=nullptr)
    {
        GeometryNode::GeometryDraw(camera, deltaTime);
        m_model->Draw(m_shader, drawMode);
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

void ModelNode::save(Stream& stream)
{
    stream.writeln(TYPE.GetName());
    if (m_model == nullptr)
        stream.writeln(AssetManager::getInstance()->noValue);
    else
        m_model->save(stream);
    //save model stuff
    GeometryNode::save(stream);


}
void ModelNode::load(Stream& stream)
{
    //eading the type line should be in the child loop, so that we create the right kind of node, we assume the type of the root node
    //if (typeName != TYPE.GetName()) PLOGE << "Wrong loader, Expected " << TYPE.GetName() << " found in file" << typeName;
    //load model stuff
    //we can just read the path here, or not
    Model* model = AssetManager::getInstance()->loadModel(stream);
    m_model = model;
    
    GeometryNode::load(stream);

}
