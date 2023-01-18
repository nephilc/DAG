#ifndef MESH_HPP
#define MESH_HPP
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <backend.hpp> // holds all OpenGL type declarations

#include <string>
#include <vector>
#include <plog/Log.h> 

#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Appenders/ColorConsoleAppender.h"
#include <Shader.hpp>
#define MAX_BONE_INFLUENCE 4
using namespace std;
//mesh class would be equivalent to a geometry class
//in glm vectors are structs
//one vertex data 88 bytes
//all this around 1.8 mBytes. for stanford bunny.
//with the indices array it is 100  bytes.
//all this data 2.2 mBytes, more data, more efficient than the text file.
//a format to store all of this directly. o post processing at loading.

//activate the right texture unit and give it the texture object, this is done independently of the shader program.
struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};
//the path is stored for optimization puposes when loading the textures in the model class
//the texture is already stored in opengl
struct Texture {
    unsigned int id;
    string type;
    string path;
};
class Mesh
{
private:
    unsigned int VBO, EBO;
    void setupMesh();
public:
    vector<Vertex>  vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;//we have all the textures loaded into opnegl, along with their types and paths
    unsigned int VAO;//this one is public could be  bound from outside.
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    ~Mesh();
    void Draw(Shader *shader);
};


#endif