#ifndef NODE_FACTORY_HPP
#define NODE_FACTORY_HPP
#include<RTTI.hpp>
#include<SceneElements.hpp>
class NodeFactory
{
private:
    /* data */
public:
    NodeFactory(/* args */);
    static Node* create(const Rtti* type);
    ~NodeFactory();
};


#endif