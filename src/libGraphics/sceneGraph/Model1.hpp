#ifndef Model1_HPP
#define Model1_HPP

#include <glad/glad.h> 

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

unsigned int TextureFromFile1(const char *path, const string &directory, bool gamma = false);

class Model1
{
public:
    // Model1 data 
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh>    meshes;
    string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D Model1.
    Model1(string const &path, bool gamma = false);
    // draws the Model1, and thus all its meshes
    void Draw(Shader *shader);    
    Node* m_scene;
private:
    void loadModel1(string const &path);
    void processNode(aiNode *node, const aiScene *scene , Node* current);
    //Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    Mesh* processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif

