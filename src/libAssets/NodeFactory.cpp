#include "NodeFactory.hpp"
std::vector<Rtti*> Rtti::typeList;
std::vector<Rtti*> Rtti::nodeList;

bool NodeFactory::initialized = false;

void NodeFactory::init()
{
    for (Rtti* type : Rtti::typeList)
    {
        if(type->IsDerived(Node::TYPE))
        {
            Rtti::nodeList.push_back(type);
        }
    }
    

}

Node *NodeFactory::create(const Rtti *type)
{
    //if(!initialized) init();
    //we can either create them directly or get the defaults from the asset manager, or add the default support in the node itself
    if(type->IsExactly(Node::TYPE))
    {
        return new Node();
    }
    else if(type->IsExactly(AnimatedNode::TYPE))
    {
    return new AnimatedNode();
    }
    else if(type->IsExactly(GeometryNode::TYPE))
    {
        PLOGE<<"geometry node matched";
    return new GeometryNode();
    }
    else if(type->IsExactly(ModelNode::TYPE))
    {
    return new ModelNode();
    }
    else
    {

    }
    return nullptr;
}

Node *NodeFactory::create(const std::string &typeName)
{
    //if(!initialized) init();
    //we can either create them directly or get the defaults from the asset manager, or add the default support in the node itself
    if(Node::TYPE.GetName() ==typeName)
    {
        return new Node();
    }
    else if(AnimatedNode::TYPE.GetName()==typeName)
    {
    return new AnimatedNode();
    }
    else if(GeometryNode::TYPE.GetName()==typeName)
    {
        PLOGE<<"geometry node matched";
    return new GeometryNode();
    }
    else if(ModelNode::TYPE.GetName()==typeName)
    {
    return new ModelNode();
    }
    else
    {

    }
    return nullptr;
}

NodeFactory::~NodeFactory()
{
}
