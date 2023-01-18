#ifndef ANIMATED_NODE_HPP
#define ANIMATED_NODE_HPP
#include "Node.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "animation.h"
#include "animator.h"
//the node needs the camera

//these seem to be unecessary, probably a residue from the early awesome face programs
//we used two textures and blended them together.
//ourShader1.setInt("texture1", 0);
    //ourShader1.setInt("texture2", 1);


class AnimatedNode : public Node
{
private:
    /* data */


public:
    AnimatedNode(Model* model, Shader* shader, Animator* animator, Animation& animation);
    ~AnimatedNode();
    void Draw(Camera* camera, float deltaTime) override;
    Model* m_model;
    //Shader& m_shader;
    Animator* m_animator;
    Animation& m_animation;



};



#endif