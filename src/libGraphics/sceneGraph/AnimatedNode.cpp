
#include "AnimatedNode.hpp"
#include<AssetManager.hpp>

IMPLEMENT_RTTI(AnimatedNode, GeometryNode)


//Animator* AnimatedNode::m_animator = nullptr;
/*void AnimatedNode::initAnimator()
{
    if(m_animator==nullptr) m_animator= new Animator();
}
*/
AnimatedNode::AnimatedNode(Model* model, Shader* shader, Animation* animation) : m_model(model),   GeometryNode(shader),
m_animation(animation)
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
    m_animator = new Animator(animation);
}
AnimatedNode::AnimatedNode():AnimatedNode(nullptr,nullptr,nullptr)
{
        //i guess we can use the asset manager here aswell.
        //AssetManager::getInstance()->loadModel("3dmodels/anotherone.fbx", "arissa2");

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
    //############################################################
    //########will need to work on a default animator#############
    //############################################################
    if(m_animator!=nullptr){
        if(m_shader!=nullptr) GeometryDraw(camera, deltaTime);
        if(play_animation)
        {
        //m_animator->PlayAnimation(m_animation);
        m_animator->UpdateAnimation(deltaTime);
        
        }
    }

    
    
    GeometryNode::Draw(camera, deltaTime);

}

void AnimatedNode::GeometryDraw(Camera *camera, float deltaTime)
{
    GeometryNode::GeometryDraw(camera, deltaTime);
    //could ask the animator to animate here
    auto transforms = m_animator->GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); ++i)//maybe needs more than 100 matrices
		m_shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
        //set the time, among other things
    if(m_model!=nullptr) m_model->Draw(m_shader, drawMode);
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

void AnimatedNode::save(Stream& stream)
{
    stream.writeln(TYPE.GetName());
    if (m_model == nullptr)
        stream.writeln(AssetManager::getInstance()->noValue);
    else
        m_model->save(stream);
 
    if (m_animation == nullptr)
        stream.writeln(AssetManager::getInstance()->noValue);
    else
        m_animation->save(stream);
    //save model stuff
    GeometryNode::save(stream);


}

void AnimatedNode::load(Stream &stream)
{
    //eading the type line should be in the child loop, so that we create the right kind of node, we assume the type of the root node
    //if (typeName != TYPE.GetName()) PLOGE << "Wrong loader, Expected " << TYPE.GetName() << " found in file" << typeName;
    //load model stuff
    m_model = AssetManager::getInstance()->loadModel(stream);

    //do the same thing for animation
    m_animation = AssetManager::getInstance()->loadAnimation(stream, m_model);
    m_animator->PlayAnimation(m_animation);
    GeometryNode::load(stream);


}

Model* AnimatedNode::getModel() 
{
    return m_model;
}
