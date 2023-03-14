////a node containing a model
#ifndef MODELNODE_HPP
#define MODELNODE_HPP

#include"Node.hpp"
#include"Model.hpp"
#include "RTTI.hpp"
class ModelNode : public Node
{
    DECLARE_RTTI
private:
    Model *m_model;
public:
    ModelNode();
    ModelNode(Model* model);
    void Draw(Camera* camera, float deltaTime) override;
    ~ModelNode();
};



#endif