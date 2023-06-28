#ifndef ANIMATED_NODE_HPP
#define ANIMATED_NODE_HPP
#include "GeometryNode.hpp"
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


class AnimatedNode : public GeometryNode
{

DECLARE_RTTI
private:
    /* data */
    bool play_animation;

public:
    //static void initAnimator();
    AnimatedNode(Model *model, Shader *shader, Animation *animation);
    AnimatedNode();
    void play();
    void stop();
    bool getPlayState();
    bool* getPlayStatePointer();
    ~AnimatedNode();
    void Draw(Camera* camera, float deltaTime) override;
    void GeometryDraw(Camera* camera, float deltaTime) override;
    Animation* getAnimation();
    void setAnimation(Animation* animation);
    Animator* getAnimator();

    Model* getModel();
    Model* m_model;
    //Shader& m_shader;
    Animator* m_animator;
    Animation* m_animation;



};



#endif