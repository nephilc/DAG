
#include "AnimatedNode.hpp"

IMPLEMENT_RTTI(AnimatedNode, GeometryNode)

AnimatedNode::AnimatedNode(Model* model, Shader* shader, Animator* animator, Animation* animation) : m_model(model),  m_animator(animator), GeometryNode(shader),
m_animation(animation)
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
    
}
/*
AnimatedNode::AnimatedNode()
{
    m_animation();//i'll need a class of defaults, defaults for every kind of class, these defaults will be provided by the asset manager
}
*/
AnimatedNode::~AnimatedNode()
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here

}

void AnimatedNode::Draw(Camera* camera, float deltaTime) 
{
    //PLOGD<<"Drawing node";
    //if(m_shader!=nullptr && m_animator!=nullptr &&m_model!=nullptr ){
    
    if(m_shader!=nullptr) GeometryDraw(camera, deltaTime);
    if(play_animation)
    m_animator->UpdateAnimation(deltaTime);


    
    
    GeometryNode::Draw(camera, deltaTime);

}

void AnimatedNode::GeometryDraw(Camera *camera, float deltaTime)
{
    GeometryNode::GeometryDraw(camera, deltaTime);
    auto transforms = m_animator->GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); ++i)
		m_shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
        //set the time, among other things
    m_model->Draw(m_shader, drawMode);
}

void AnimatedNode::play() { if( m_animation!=nullptr) play_animation = true; }
void AnimatedNode::stop() { play_animation = false; }
bool AnimatedNode::getPlayState() { return play_animation; }

bool *AnimatedNode::getPlayStatePointer()
{
    return &play_animation;
}


Animation* AnimatedNode::getAnimation()
{
    return m_animation;
}
void AnimatedNode::setAnimation(Animation* animation)
{
    m_animation = animation;
}

Animator* AnimatedNode::getAnimator() 
{
    return m_animator;
}

Model* AnimatedNode::getModel() 
{
    return m_model;
}
