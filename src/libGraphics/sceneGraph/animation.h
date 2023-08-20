

#ifndef ANIMATION_H 
#define ANIMATION_H


#include <vector>
#include <map>
#include <glm.hpp>
#include <assimp/scene.h>
#include <bone.h>
#include <functional>
#include <animData.h>
#include <Model.hpp>
#include <plog/Log.h>
#include<Object.hpp>

//#include<AssetManager.hpp>

//load an animation for a specific model.
//give it the loaded model and the path of the animation, which could be in the same model.
//will need to create a bunch of these for every model.


// this is a graph
struct AssimpNodeData
{
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector<AssimpNodeData> children;
};

class Animation : public Object
{
public:
	DECLARE_RTTI

	std::string animationPath;
	Animation() = default;
	Animation(const aiScene* scene, Model* model)
	{
		assert(scene && scene->mRootNode);//this is the assertion that gives errors, when i try to load thos other files
		auto animation = scene->mAnimations[0];//we take the first animation., there could be multiple animation loaded
		PLOGI << "NUMBER OF ANIMATIONS IN THIS MODEL IS " << scene->mNumAnimations;
		m_Duration = animation->mDuration;//the duration is to be used outside of the animation
		PLOGD<<"ANIMATION DURATION IS"<<m_Duration;
		m_TicksPerSecond = animation->mTicksPerSecond;
		PLOGD<<"ANIMATION DURATION IS"<<m_TicksPerSecond;
		
		aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;//transform relative to the nodes parent, should use this one in general

		globalTransformation = globalTransformation.Inverse();
		ReadHeirarchyData(m_RootNode, scene->mRootNode);
		ReadMissingBones(animation, *model);

		//object method
		SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here

	}
	Animation(const std::string& animationPath, Model* model)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
		assert(scene && scene->mRootNode);//this is the assertion that gives errors, when i try to load thos other files
		auto animation = scene->mAnimations[0];//we take the first animation.
		PLOGI<<"NUMBER OF ANIMATIONS IN THIS MODEL IS "<<scene->mNumAnimations;
		m_Duration = animation->mDuration;//the duration is to be used outside of the animation
		m_TicksPerSecond = animation->mTicksPerSecond;
		aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;

		globalTransformation = globalTransformation.Inverse();
		ReadHeirarchyData(m_RootNode, scene->mRootNode);
		ReadMissingBones(animation, *model);
		SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here

	}

	~Animation()
	{
	}
	//this one is called by the animator
	Bone* FindBone(const std::string& name)
	{
		auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),
			[&](const Bone& Bone)
			{
				return Bone.GetBoneName() == name;
			}
		);
		if (iter == m_Bones.end()) return nullptr;
		else return &(*iter);
	}

	//#####################################A bunch of getter methods#################################
	inline float GetTicksPerSecond() { return m_TicksPerSecond; }
	inline float GetDuration() { return m_Duration;}
	inline const AssimpNodeData& GetRootNode() { return m_RootNode; }
	inline const std::map<std::string,BoneInfo>& GetBoneIDMap() 
	{ 
		return m_BoneInfoMap;
	}
	//###############################################################################################

	//this is a static utility method, return a pointer to a loaded animation.
	static Animation* loadAnimation(const std::string& animationPath, Model* model)
	{


		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
		assert(scene && scene->mRootNode);//this is the assertion that gives errors, when i try to load thos other files
		/*
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
			return nullptr;
		}
		*/
		Animation* animation = new Animation(scene, model);

		//animation->animationPath = AssetManager::getInstance()->getSplitPathUsingBasePath(animationPath);
		animation->animationPath = animationPath;
		
		return animation;

		
	};
	void load(Stream& stream);
	void save(Stream& stream);


private:
//called second, now we read bone data, not recurs
//does twothings: always adds bone/channel to bone vector
//if bonnes doesnt exist inn bone info map it adds it
	void ReadMissingBones(const aiAnimation* animation, Model& model)
	{
		int size = animation->mNumChannels;
		//
	PLOGD<<"NUMBER OF CHANNELS IS:"<<size; 

		//so the model reads som bone info, this bone info is not specific to one animation
		//we get an id and an offset
		//so we map the name of a bone to its (its id and offsset, that id is also used in the finalbones matrix)
		auto& boneInfoMap = model.GetBoneInfoMap();//getting m_BoneInfoMap from Model class
		int& boneCount = model.GetBoneCount(); //getting the m_BoneCounter from Model class
		PLOGD<<"BONE COUNT FOR THIS ANIMATION IS: "<<boneCount; 
		//so each channel seems to have some part of the animation
		//reading channels(bones engaged in an animation and their keyframes)
		for (int i = 0; i < size; i++)
		{
			auto channel = animation->mChannels[i];//this array hold aiNodeAnim's, whik hold keys for rotation position and scaling, a key is a pair(time, value(vector, quaternion, or else))
			std::string boneName = channel->mNodeName.data;
			PLOGD<<"CHANNEL "<< i<<" Affect the node :"<< boneName;
			//so we exclude the channels that affect the fingers
			if (boneInfoMap.find(boneName) == boneInfoMap.end())
			{
				PLOGE<<"didnt find this one "<<boneName;
				boneInfoMap[boneName].id = boneCount;
				boneCount++;
			}
			PLOGD<<"Matrix id in array for this Bone/channel is "<<boneInfoMap[channel->mNodeName.data].id;
			//this is where bone objects are created
			m_Bones.push_back(Bone(channel->mNodeName.data,
				boneInfoMap[channel->mNodeName.data].id, channel));//a channel is specific to a bone, and it holds keyframe data for a bone
		}	//we can find the id for the bone
		PLOGD<<"number of bones after missing"<<m_Bones.size();//something doesnt add up
		m_BoneInfoMap = boneInfoMap;
	}

	//an animation is made up of channels
	//called first
//goes through every node in the scene, also pass parent node data to the chilren, maybe the transforms for the fingers are wrong
	void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src)//so this isnt bone data this is just normal, hierarchy data, scene data.
	{
		assert(src);

		dest.name = src->mName.data;
		PLOGD<<"NODE NAME "<< dest.name;
		dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);//pass the parent's local transform to the children
		dest.childrenCount = src->mNumChildren;

		for (unsigned int i = 0; i < src->mNumChildren; i++)
		{
			AssimpNodeData newData;
			ReadHeirarchyData(newData, src->mChildren[i]);
			dest.children.push_back(newData);
		}
	}
	float m_Duration;
	int m_TicksPerSecond;
	std::vector<Bone> m_Bones;
	AssimpNodeData m_RootNode;//this is a graph, yet it is done without pointers, filled with ReadHeirarchyData() method
	std::map<std::string, BoneInfo> m_BoneInfoMap;
};

#endif