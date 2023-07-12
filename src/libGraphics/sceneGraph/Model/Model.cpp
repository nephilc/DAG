#include "Model.hpp"
#include <plog/Log.h>
#include <assimp/postprocess.h>


Model::Model(string const &path, string const& fileName, bool gamma) : gammaCorrection(gamma), path(path), fileName(fileName) 
{
        cout<<"calling model constructor"<<endl;
        //loadModel(path);
}
 void Model::Draw(Shader *shader, DrawMode MD)
 {
        //shader.setMat4("model", model);
        for(unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader, MD);
}
   
//loading texture image from file and putting it in opengl.
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
    string filename = string(path);
    filename = directory + '/' + filename;


    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    unsigned int textureID;

    if (data)
    {
        backend::getBackend()->createTextureModel(&textureID, nrComponents, width, height, data);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    Model* Model::loadModel(string const& path,string const& fileName, bool gamma)
    {
        PLOGD<<"calling Model Loader";

        Model* model = new Model(path, fileName);

        // read file via ASSIMP
        Assimp::Importer importer;
        //importer.SetPropertyFloat(AI_CONFIG_GLOBAL_SCALE_FACTOR_KEY, 0.01);

        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);


/*
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
            return nullptr;
        }
*/
        // check for errors
        //double factor1(0.0);
        //scene->mMetaData->Get("UnitScaleFactor", model->factor);
        //factor = factor1;

        model->numAnimations = scene->mNumAnimations;
        model->numCameras = scene->mNumCameras;
        model->numMaterials = scene->mNumMaterials;
        model->numTextures = scene->mNumTextures;
        model->numLights = scene->mNumLights;
        model->numMeshes = scene->mNumMeshes;
        // retrieve the directory path of the filepath
        model->directory = path.substr(0, path.find_last_of('/'));
        if(scene->HasTextures())
            model->m_scene = new Node();
        // process ASSIMP's root node recursively
        model->processNode(scene->mRootNode, scene);
        return model;
    }
    //

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void Model::processNode(aiNode *node, const aiScene *scene)
    {
        PLOGD<<"NUMBER OF MESHES IN THIS NODE:" << node->mName.C_Str()<<"IS "<< node->mNumMeshes;

        // process each mesh located at the current node
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // the node object only contains indices to index the actual objects in the scene. 
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            if(scene->HasTextures())
            {
            meshes.push_back(processMesh(mesh, scene));

            }
            else{
            meshes.push_back(processMesh(mesh, scene));
            }
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }

    }

    Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
    {
        vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;
		

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			SetVertexBoneDataToDefault(vertex);
			vertex.Position = AssimpGLMHelpers::GetGLMVec(mesh->mVertices[i]);
			vertex.Normal = AssimpGLMHelpers::GetGLMVec(mesh->mNormals[i]);
			
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        //material->GetTexture();
        //scene->GetEmbeddedTexture().

		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular" , scene);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal",  scene);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", scene);
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        //scene->GetEmbeddedTexture()->pcData
        //they say the format is argb8888
        //GL_RGBA8, perhaps we use this format
    //    GL_BG
        //aiTexel is a cstruct of bgra,which means we can pass it directly to opengl.

		ExtractBoneWeightForVertices(vertices,mesh,scene);

		return Mesh(vertices, indices, textures);    
}//
    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    //the type of a texture, the type name of a texture.
    //this method loads textures of a certain type.
    vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName,const aiScene* scene)
    {
        vector<Texture> textures;
        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;//name of the texture in the material
            mat->GetTexture(type, i, &str);
            PLOGI<<"texture name is "<<str.C_Str(); 

            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for(unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if(!skip)
            {   // if texture hasn't been loaded already, load it
                Texture texture;
                if(scene->HasTextures())
                {                
                    PLOGI<<"this one has textures";
                    texture.id = TextureFromFile_EM(str.C_Str(), this->directory, scene);
                    
                }
                else
                {
                texture.id = TextureFromFile(str.C_Str(), this->directory);
                }
                //another cse when the texture is embedded. We will not have 
                //scene->GetEmbeddedTexture()
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
    }

//loading texture image from file and putting it in opengl.
unsigned int TextureFromFile_EM(const char *path, const string &directory, const aiScene* scene, bool gamma)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    const aiTexture* texture = scene->GetEmbeddedTexture(path);

    
    int width, height, components_per_pixel;

    unsigned char *data = nullptr;
    if (texture->mHeight == 0)
    {
	    data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData), texture->mWidth, &width, &height, &components_per_pixel, 0);
    }
    else
    {
	    data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData), texture->mWidth * texture->mHeight, &width, &height, &components_per_pixel, 0);
    }
    ///////////////////
    unsigned int textureID;

    if (true)
    {
        backend::getBackend()->createTextureModel(&textureID, components_per_pixel, width, height, data);

        //stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        //stbi_image_free(data);
    }

    return textureID;
}
