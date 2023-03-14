#ifndef GEOMETRYNODE_HPP
#define GEOMETRYNODE_HPP
#include "Node.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "animation.h"
#include "animator.h"

#include<RTTI.hpp>
//the node needs the camera

//these seem to be unecessary, probably a residue from the early awesome face programs
//we used two textures and blended them together.
//ourShader1.setInt("texture1", 0);
    //ourShader1.setInt("texture2", 1);


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