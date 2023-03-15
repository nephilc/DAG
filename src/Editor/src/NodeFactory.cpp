#include "NodeFactory.hpp"
std::vector<Rtti*> Rtti::typeList;

Node *NodeFactory::create(const Rtti *type)
{
    //we can either create them directly or get the defaults from the asset manager, or add the default support in the node itself
    if(type->IsExactly(Node::TYPE)){
        return new Node();
    }
    else if(type->IsExactly(ModelNode::TYPE)){
    return new ModelNode();
    }
    else{

    }
    return nullptr;
}

NodeFactory::~NodeFactory()
{
}
