#ifndef GEOMETRYNODE_HPP
#define GEOMETRYNODE_HPP
#include "Node.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "animation.h"
#include "animator.h"

#include<RTTI.hpp>

//the objectif of this class is to handle some generic stuff related to shaders, and any operations to be perfored by objects that use shaders, and/or render any geometry.

class GeometryNode : public Node
{

DECLARE_RTTI
protected:
    /* data */
    Shader* m_shader;



public:
    GeometryNode(Shader* shader);
    GeometryNode();
    ~GeometryNode();
    void setShader(Shader* shader);    
    Shader* getShader();    

    void Draw(Camera* camera, float deltaTime) override;
    //only call this, starting from child methods
    virtual void GeometryDraw(Camera* camera, float deltaTime);
    //Shader& m_shader;


};



#endif