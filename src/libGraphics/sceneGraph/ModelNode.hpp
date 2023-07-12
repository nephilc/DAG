////a node containing a model
#ifndef MODELNODE_HPP
#define MODELNODE_HPP

#include"GeometryNode.hpp"
#include"Model.hpp"
#include "RTTI.hpp"
class ModelNode : public GeometryNode
{
    DECLARE_RTTI
private:
    Model *m_model;
public:
    ModelNode();
    ModelNode(Model* model);
    void Draw(Camera* camera, float deltaTime) override;
    void GeometryDraw(Camera* camera, float deltaTime) override;
    void setModel(Model *model);

    Model *getModel();

    //load
    //save
    void save(Stream& stream) override;
    void load(Stream& stream);

    ~ModelNode();
};



#endif