

#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <glm.hpp>
#include <map>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <animation.h>
#include <bone.h>
//takes an animation, will need to create one of these for every animation.
//the animator will give us the bones matrices that we will pass to the shaders. after updating 
//the animation.
//we can have up to 100 bones, and hence up to 100 matrices.
//we set them at every render cycle for the animated model. however, every vertex can be 
//influenced with only 4 bones, and hence will be multiplied by up to 4 matrices
//in the animation part, we can change the max bone influence.
//we have the ids of the bones that influence this exact vertex

//bone id and weight is independent of animation


//so we could load the bone info, independently of animation.
//we can add a setter, set current animation to work with different animations.

class Animator
{
public:
	Animator()
	{
		m_CurrentTime = 0.0;

		m_FinalBoneMatrices.reserve(100);//we set the limit to 100 in the animator class.

		for (int i = 0; i < 100; i++)
			m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
	}
	Animator(Animation* animation)
	{
		m_CurrentTime = 0.0;
		m_CurrentAnimation = animation;

		m_FinalBoneMatrices.reserve(100);//we set the limit to 100 in the animator class.

		for (int i = 0; i < 100; i++)
			m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
	}

	void UpdateAnimation(float dt)
	{
		m_DeltaTime = dt;
		if (m_CurrentAnimation!=nullptr)
		{
			m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * dt;
			m_CurrentTime = fmod(m_CurrentTime, m_CurrentAnimation->GetDuration());
			CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
		}
	}

	//change the current Animation
	void PlayAnimation(Animation* pAnimation)
	{
		m_CurrentAnimation = pAnimation;
		m_CurrentTime = 0.0f;
	}
	//maybe when computing the transforms recursively we mess up when we reach the fingers
//calculating bone transforms recursively.
	void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform)
	{
		std::string nodeName = node->name;
		glm::mat4 nodeTransform = node->transformation;

		Bone* Bone = m_CurrentAnimation->FindBone(nodeName);

		if (Bone)
		{
			Bone->Update(m_CurrentTime);
			nodeTransform = Bone->GetLocalTransform();
		}

		glm::mat4 globalTransformation = parentTransform * nodeTransform;

		auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
		if (boneInfoMap.find(nodeName) != boneInfoMap.end())
		{
			int index = boneInfoMap[nodeName].id;
			glm::mat4 offset = boneInfoMap[nodeName].offset;
			m_FinalBoneMatrices[index] = globalTransformation * offset;
		}

		for (int i = 0; i < node->childrenCount; i++)
			CalculateBoneTransform(&node->children[i], globalTransformation);
	}

	std::vector<glm::mat4> GetFinalBoneMatrices()
	{
		return m_FinalBoneMatrices;
	}

private:
	std::vector<glm::mat4> m_FinalBoneMatrices;//these are the ones we pass to the shader
	Animation* m_CurrentAnimation;//we use this animation to update the finalBoneMatrices
	float m_CurrentTime;
	float m_DeltaTime;

};

#endif