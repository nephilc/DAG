#include "Shader.hpp"

//the shader doesnn't know which backend it is using
Shader::Shader(const char* vertexPath, const char* fragmentPath)
    {
        m_vertexPath.assign(vertexPath);
        m_fragmentPath.assign(fragmentPath);
        load(vertexPath, fragmentPath);
        
    }

 void Shader::use() 
    { 
       backend::getBackend()->useProgram(ID);
    }

void Shader::setBool(const std::string &name, bool value) const
    {         
        backend::getBackend()->setBool(ID,name,value);
    }
    // -
    void Shader::setInt(const std::string &name, int value) const
    { 
        backend::getBackend()->setInt(ID,name,value);
    }
        void Shader::setFloat(const std::string &name, float value) const
    { 
        backend::getBackend()->setFloat(ID,name,value);
    }

        void Shader::checkCompileErrors(unsigned int shader, std::string type)
    {
        backend::getBackend()->checkCompileErrors(shader, type);
    }

void Shader::load(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        ID = backend::getBackend()->createProgram(vShaderCode, fShaderCode);

}

void Shader::reload()
{
    backend::getBackend()->deleteProgram(ID);
    load(m_vertexPath.c_str(), m_fragmentPath.c_str());

}

//i need a macro
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
    { 
        backend::getBackend()->setVec2(ID,name,value);
    };
    void Shader::setVec2(const std::string &name, float x, float y) const
    { 
        backend::getBackend()->setVec2(ID,name,x,y);
    };
    // ------------------------------------------------------------------------
    void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        backend::getBackend()->setVec3(ID,name,value);
    };
    void Shader::setVec3(const std::string &name, float x, float y, float z) const
    { 
        backend::getBackend()->setVec3(ID,name,x,y,z);
    };
    // ------------------------------------------------------------------------
    void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        backend::getBackend()->setVec4(ID,name,value);
    };
    void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
    { 
        backend::getBackend()->setVec4(ID,name,x,y,z,w);
    };
    // ------------------------------------------------------------------------
    void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        backend::getBackend()->setMat2(ID,name,mat);
    };
    // ------------------------------------------------------------------------
    void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        backend::getBackend()->setMat3(ID,name,mat);
    };
    // ------------------------------------------------------------------------
    void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        backend::getBackend()->setMat4(ID,name,mat);
    };
