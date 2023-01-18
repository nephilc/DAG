
#include "AnimatedNode.hpp"


AnimatedNode::AnimatedNode(Model* model, Shader* shader, Animator* animator, Animation& animation) : m_model(model),  m_animator(animator),
m_animation(animation)
{
    Node::m_shader = shader;
}

AnimatedNode::~AnimatedNode()
{
}

void AnimatedNode::Draw(Camera* camera, float deltaTime) 
{
    //PLOGD<<"Drawing node";
    
    m_animator->UpdateAnimation(deltaTime);

    m_shader->use();

    auto transforms = m_animator->GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); ++i)
		m_shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

    
    m_shader->setMat4("projection", Node::projection);
	m_shader->setMat4("view", camera->GetViewMatrix());
        
    m_shader->setMat4("model", m_world);
    m_model->Draw(m_shader);

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