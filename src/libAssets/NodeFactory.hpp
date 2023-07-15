#ifndef NODE_FACTORY_HPP
#define NODE_FACTORY_HPP
#include<RTTI.hpp>
#include<SceneElements.hpp>
class NodeFactory
{
private:
    /* data */
    static bool initialized;
public:
    NodeFactory(/* args */);
    static void init();
    static Node *create(const Rtti *type);
    ~NodeFactory();
};


#endif