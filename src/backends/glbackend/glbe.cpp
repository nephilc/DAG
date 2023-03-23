#include"glbe.hpp"

//could use a macro function
//needs to be called first by the client.
//could add a static initbackend method
glbe* glbe::getBackend()
{
    if(be == 0)
    {
        be = new glbe();
        return (glbe*)be;
    }
    return (glbe*)be;
}
void glbe::clearColorAndBuffersDC(float r, float g, float b, float a) const
{
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

}

void glbe::createTextureModel(unsigned int *textureID,int nrComponents, int width, int height, unsigned char *data)
{
    glGenTextures(1, textureID);
    GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, *textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}


glbe::glbe()
{
}

void glbe::displayTest()
{
    PLOGI<<"glbe test";
}


glbe::~glbe()
{
}

void glbe::setVec2(unsigned int ID,const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    };
void glbe::setVec2(unsigned int ID,const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
    };
    // ------------------------------------------------------------------------
void glbe::setVec3(unsigned int ID,const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    };
void glbe::setVec3(unsigned int ID,const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
    };
    // ------------------------------------------------------------------------
void glbe::setVec4(unsigned int ID,const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    };
void glbe::setVec4(unsigned int ID,const std::string &name, float x, float y, float z, float w) const
    { 
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
    };
    // ------------------------------------------------------------------------
void glbe::setMat2(unsigned int ID,const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    };
    // ------------------------------------------------------------------------
void glbe::setMat3(unsigned int ID,const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    };
    // ------------------------------------------------------------------------
void glbe::setMat4(unsigned int ID,const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    };

void glbe::use(unsigned int ID) 
    { 
        glUseProgram(ID); 
    }

void glbe::setBool(unsigned int ID,const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    // -
void glbe::setInt(unsigned int ID,const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
void glbe::setFloat(unsigned int ID,const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }

void glbe::checkCompileErrors(unsigned int shader, std::string type)
{

        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
}


void glbe::useProgram(unsigned int ID)
{
    glUseProgram(ID);
}

int glbe::createProgram(const char* vShaderCode, const char* fShaderCode)
{
    // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        unsigned int ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return ID;
}

void glbe::create2DSquare(unsigned int* VAO, unsigned int* VBO, const float* vertices, unsigned int size) const 
{
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}

void glbe::deleteProgram(unsigned int ID)
{
    glDeleteProgram(ID);
}

void glbe::createMesh(unsigned int *VAO,unsigned int *VBO,unsigned int *EBO, unsigned int offsets[6], const void* vertices, unsigned int size
, const void* indices, unsigned int isize, unsigned int vsize)
{

// create buffers/arrays
        glGenVertexArrays(1, VAO);
        glGenBuffers(1, VBO);
        glGenBuffers(1, EBO);

        glBindVertexArray(*VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, size * vsize, vertices, GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vsize, (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vsize, (void*)offsets[0]);
        // vertex texture coords
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vsize, (void*)offsets[1]);
        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vsize, (void*)offsets[2]);
        // vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, vsize, (void*)offsets[3]);
		// ids
		glEnableVertexAttribArray(5);
		glVertexAttribIPointer(5, 4, GL_INT, vsize, (void*)offsets[4]);

		// weights
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, vsize, (void*)offsets[5]);
        glBindVertexArray(0);

}

void glbe::drawMesh(unsigned int VAO, unsigned int sindex)
{
            // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(sindex), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);


}
void glbe::drawSurface(unsigned int VAO, unsigned int sindex)
{
    // draw mesh
    glBindVertexArray(VAO);
    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glEnable(GL_DEPTH_TEST);


}

//texture unit, texture ID, shader ID, uniform sampler name
void glbe::setTexture(unsigned int unit, unsigned int textureID, unsigned int shaderID, const char* name)
{
     glActiveTexture(GL_TEXTURE0 + unit); // active proper texture unit before binding

            // now set the sampler to the correct texture unit(for example: texture_diffuse2)
            glUniform1i(glGetUniformLocation(shaderID, name), unit);
            
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, textureID);
            //for every texture activate a  texture unit, poi

            //you bind a texture to a texture unit and, then set the sampler to the correct texture unit.
       
}

void glbe::viewport(float x, float y, float width, float height) const
{
    glViewport(x, y, width, height);
}
