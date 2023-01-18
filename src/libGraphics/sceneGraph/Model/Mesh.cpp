#include "Mesh.hpp"
//well, the indices array gives us info about which vertices a face is made of.
//the Vertex array gives us all the info about each vertex(coords, texture coords, 
// normal, tangent...)
//the way assimp works is that a vertex and its data has the same index in all the arrays.
//unlike obj where all the info comes toghether when specifying faces.
//we can manage to pass a struct of vertex to opengl
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
    this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        PLOGE<<sizeof(glm::vec3) << " " << sizeof(Vertex);
        PLOGE<<"creating mesh";
        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
}

Mesh::~Mesh()
{
}

//will have to pass the offsets as parametres, in an array
//vao, vbo, ebo
void Mesh::setupMesh()
{
        //PLOGD<<"DID SETUP MESH";
        unsigned int offsets[6] = {offsetof(Vertex, Normal),offsetof(Vertex, TexCoords),offsetof(Vertex, Tangent),offsetof(Vertex, Bitangent),offsetof(Vertex, m_BoneIDs),offsetof(Vertex, m_Weights)};
        backend::getBackend()->createMesh(&VAO,&VBO,&EBO, offsets, &vertices[0], vertices.size()
, &indices[0], indices.size(), sizeof(Vertex));

}

//the mesh will have its own shader, possessing certain attributes and uniforms, it will know about.
//one mesh can have many textures of the same kind.
void Mesh::Draw(Shader *shader)
{
 // bind appropriate textures
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;
        for(unsigned int i = 0; i < textures.size(); i++)
        {
            // retrieve texture number (the N in diffuse_textureN)
            string number;
            string name = textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to string
            else if(name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to string
             else if(name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to string

    backend::getBackend()->setTexture(i, textures[i].id, shader->ID, (name + number).c_str());

            }
    backend::getBackend()->drawMesh(VAO, indices.size());        
}
