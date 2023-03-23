#ifndef backend_HPP
#define backend_HPP

#include <gtc/matrix_transform.hpp>
#include<string>
#include<iostream>
class backend
{
protected:
    static backend* be;
    backend(/* args */);
    ~backend();

public:
virtual    void displayTest() =0;
virtual    void createTextureModel(unsigned int *textureID,int nrComponents, int width, int height, unsigned char *data) =0;
static     backend* getBackend();

virtual    void use(unsigned int ID)=0;

virtual    void setBool(unsigned int ID,const std::string &name, bool value) const=0;
virtual    void setInt(unsigned int ID,const std::string &name, int value) const=0;
virtual    void setFloat(unsigned int ID,const std::string &name, float value) const=0;
//if i add a call to use shader, the client wont have to call it themselves, since we are already passing the shader id.
virtual    void setVec2(unsigned int ID,const std::string &name, const glm::vec2 &value) const=0;
virtual    void setVec2(unsigned int ID,const std::string &name, float x, float y) const=0;
virtual    void setVec3(unsigned int ID,const std::string &name, const glm::vec3 &value) const=0;
virtual    void setVec3(unsigned int ID,const std::string &name, float x, float y, float z) const=0;
virtual    void setVec4(unsigned int ID,const std::string &name, const glm::vec4 &value) const=0;
virtual    void setVec4(unsigned int ID,const std::string &name, float x, float y, float z, float w) const=0;
virtual    void setMat2(unsigned int ID,const std::string &name, const glm::mat2 &mat) const=0;
virtual    void setMat3(unsigned int ID,const std::string &name, const glm::mat3 &mat) const=0;
virtual    void setMat4(unsigned int ID,const std::string &name, const glm::mat4 &mat) const=0;
virtual    void clearColorAndBuffersDC(float r, float g, float b, float a) const=0;
virtual void drawSurface(unsigned int VAO, unsigned int sindex)=0;


virtual void create2DSquare(unsigned int* VAO, unsigned int* VBO, const float* vertices, unsigned int size) const=0;

virtual    void checkCompileErrors(unsigned int shader, std::string type) =0;

virtual void useProgram(unsigned int ID)=0;
virtual int createProgram(const char* vShaderCode, const char* fShaderCode)=0;
virtual void deleteProgram(unsigned int ID)=0;
virtual void createMesh(unsigned int *VAO,unsigned int *VBO,unsigned int *EBO, unsigned int offsets[6], const void* vertices, unsigned int size
, const void* indices, unsigned int isize, unsigned int vsize)=0;
virtual void drawMesh(unsigned int VAO, unsigned int sindex)=0;
virtual void setTexture(unsigned int unit, unsigned int textureID, unsigned int shaderID, const char* name)=0;

//a render call that takes the framebufferas a parametre
};
//undefined referencec to vtable, if methods are not pure virtual and not defined
#endif
