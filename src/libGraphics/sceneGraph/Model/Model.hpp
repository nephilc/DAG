

#ifndef MODEL_HPP
#define MODEL_HPP

#include <backend.hpp> 

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>
#include <Mesh.hpp>
#include <Shader.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


using namespace std;
#include <plog/Log.h> 

#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Appenders/ColorConsoleAppender.h"
#include "Node.hpp"



#include <assimp_glm_helpers.h>
#include <animData.h>

#include<Object.hpp>

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
unsigned int TextureFromFile_EM(const char *path, const string &directory,const aiScene* scene,bool gamma = false);
//when it comes to the persistance of models, you only need to save their paths, theiy will be reloaded by assimp.
//and maybe that gamma correction. but that wouldnt be a problem
class Model : public Object
{
public:
	DECLARE_RTTI


	//importznt attributes for not reloading files twice
	std::string fileName;
	std::string path;

    // model data 
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh>    meshes;
    string directory;
    bool gammaCorrection;
    Node* m_scene;
	bool embedded;
	double factor;
	int numAnimations, numCameras, numMaterials, numTextures, numLights, numMeshes ;
    // constructor, expects a filepath to a 3D model.
    Model(string const &path, string const &fileName, bool gamma = false);
    // draws the model, and thus all its meshes
    void Draw(Shader *shader, DrawMode MD);
    //animation stuff
    auto& GetBoneInfoMap() { return m_BoneInfoMap; }
	int& GetBoneCount() { return m_BoneCounter; }
	void SetVertexBoneDataToDefault(Vertex& vertex)
	{
		for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
		{
			vertex.m_BoneIDs[i] = -1;
			vertex.m_Weights[i] = 0.0f;
		}
	}
    void SetVertexBoneData(Vertex& vertex, int boneID, float weight)
	{
		for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
		{
			if (vertex.m_BoneIDs[i] < 0)
			{
				vertex.m_Weights[i] = weight;
				vertex.m_BoneIDs[i] = boneID;
				break;
			}
		}
	}


	void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene)
	{
		auto& boneInfoMap = m_BoneInfoMap;
		int& boneCount = m_BoneCounter;
		PLOGD<<"number of bones in mesh " <<mesh->mName.C_Str()<<" is"<< mesh->mNumBones;

		for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
		{
			int boneID = -1;
			std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
			if (boneInfoMap.find(boneName) == boneInfoMap.end())
			{
				BoneInfo newBoneInfo;
				newBoneInfo.id = boneCount;
				newBoneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
				boneInfoMap[boneName] = newBoneInfo;
				boneID = boneCount;
				boneCount++;
			}
			else
			{
				boneID = boneInfoMap[boneName].id;
			}
			assert(boneID != -1);
			auto weights = mesh->mBones[boneIndex]->mWeights;
			int numWeights = mesh->mBones[boneIndex]->mNumWeights;

			for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
			{
				int vertexId = weights[weightIndex].mVertexId;
				float weight = weights[weightIndex].mWeight;
				assert(vertexId <= vertices.size());
				SetVertexBoneData(vertices[vertexId], boneID, weight);
			}
		}
	}
	static Model* loadModel(string const& path, string const& fileName, bool gamma = false);

	//persistance
	void load(Stream& stream);
	void save(Stream& stream);


private:
//animation stuff
    std::map<string, BoneInfo> m_BoneInfoMap;
	int m_BoneCounter = 0;
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    //Mesh processMesh_Em(aiMesh *mesh, const aiScene *scene);//models with embedded textures
    //Mesh* processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName, const aiScene* scene);
};

#endif

