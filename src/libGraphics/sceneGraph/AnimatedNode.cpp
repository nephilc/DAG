
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
    m_animator->UpdateAnimation(deltaTime);

    m_shader->use();

    auto transforms = m_animator->GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); ++i)
		m_shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
        //set the time, among other things
    
    m_shader->setMat4("projection", Node::projection);
	m_shader->setMat4("view", camera->GetViewMatrix());
        
    m_shader->setMat4("model", m_world);
    m_model->Draw(m_shader);
    //}
    Node::Draw(camera, deltaTime);
    //PLOGD<<"Node" <<this->GetName();

    /*for(int i = 0; i < m_meshData.size(); ++i)
    {
        m_meshData[i]->Draw(shader);
    }*/
    /*Node::Draw();
    for(int i = 0; i <m_children.size(); ++i)
    {
        m_children[i]->Draw(shader);
    }*/

}