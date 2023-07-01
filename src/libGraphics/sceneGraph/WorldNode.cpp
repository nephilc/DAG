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
    //only clear color if parent is non null, meaning we are root in the entire scene.
    if(Node::m_parent==nullptr)
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

void WorldNode::save(Stream &stream)
{
    stream.writeln(TYPE.GetName());
    stream.writeln(4, clearColor);
    Node::save(stream);

}

void WorldNode::load(Stream &stream)
{
    string typeName = stream.readln();//eading the type line should be in the child loop, so that we create the right kind of node, we assume the type of the root node
    if (typeName != TYPE.GetName()) PLOGE << "Wrong loader, Expected " << TYPE.GetName() << " found in file" << typeName;
    stream.readln(4, clearColor);
    Node::load(stream);

}

WorldNode::~WorldNode()
{
}