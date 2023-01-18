#ifndef GLBE_HPP
#define GLBE_HPP
//this onee will have the factory method
//dividing the singleton on a hierarchy
//the user will call the appropriate class
#include"backend.hpp"
//#include <GLES3/gl3.h>//i included this one when developpping for android
#include <glad/glad.h>

#include<iostream>
class glbe : public backend
{
private:
    /* data */
    glbe(/* args */);

public:
    static glbe* getBackend();
    void displayTest();
    void createTextureModel(unsigned int *textureID, int nrComponents, int width, int height, unsigned char *data);
void use(unsigned int ID);

void setBool(unsigned int ID,const std::string &name, bool value) const;
void setInt(unsigned int ID,const std::string &name, int value) const;
void setFloat(unsigned int ID,const std::string &name, float value) const;

void setVec2(unsigned int ID,const std::string &name, const glm::vec2 &value) const;
void setVec2(unsigned int ID,const std::string &name, float x, float y) const;
void setVec3(unsigned int ID,const std::string &name, const glm::vec3 &value) const;
void setVec3(unsigned int ID,const std::string &name, float x, float y, float z) const;
void setVec4(unsigned int ID,const std::string &name, const glm::vec4 &value) const;
void setVec4(unsigned int ID,const std::string &name, float x, float y, float z, float w) const;
void setMat2(unsigned int ID,const std::string &name, const glm::mat2 &mat) const;
void setMat3(unsigned int ID,const std::string &name, const glm::mat3 &mat) const;
void setMat4(unsigned int ID,const std::string &name, const glm::mat4 &mat) const;
void checkCompileErrors(unsigned int shader, std::string type);
void useProgram(unsigned int ID);
int createProgram(const char* vShaderCode, const char* fShaderCode);
void deleteProgram(unsigned int ID);
void createMesh(unsigned int *VAO,unsigned int *VBO,unsigned int *EBO, unsigned int offsets[6], const void* vertices, unsigned int size
, const void* indices, unsigned int isize, unsigned int vsize);
void drawMesh(unsigned int VAO, unsigned int sindex);
void setTexture(unsigned int unit, unsigned int textureID, unsigned int shaderID, const char* name);
    ~glbe();
};

#endif