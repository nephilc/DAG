
#include "AnimatedNode.hpp"

IMPLEMENT_RTTI(AnimatedNode, GeometryNode)

AnimatedNode::AnimatedNode(Model* model, Shader* shader, Animator* animator, Animation& animation) : m_model(model),  m_animator(animator), GeometryNode(shader),
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
    
    GeometryDraw(camera, deltaTime);
    m_animator->UpdateAnimation(deltaTime);


    auto transforms = m_animator->GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); ++i)
		m_shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
        //set the time, among other things
    m_model->Draw(m_shader);
    
    GeometryNode::Draw(camera, deltaTime);

}

void AnimatedNode::GeometryDraw(Camera *camera, float deltaTime)
{
    GeometryNode::GeometryDraw(camera, deltaTime);
}
