#include"NDCsquare.hpp"


IMPLEMENT_RTTI(NDCsquare, Object)

Shader* NDCsquare::frameshader = nullptr;
unsigned int NDCsquare::VBO=0;
unsigned int NDCsquare::VAO=0;
float NDCsquare::quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};


NDCsquare::NDCsquare()
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
    frameshader = new Shader("shaderPrograms/framebuffer.vs", "shaderPrograms/framebuffer.fs");
    //backend::getBackend()->viewport(0, 0, 10, 10);
    loadGeometry();

}

void NDCsquare::setShader(Shader *shader)
{
    frameshader = shader;
}

Shader* NDCsquare::getShader()
{
    return frameshader;
}

NDCsquare::~NDCsquare()
{
}


void NDCsquare::loadGeometry()
{
    backend::getBackend()->create2DSquare(&VAO, &VBO, &quadVertices[0], sizeof(quadVertices));
   
}

void NDCsquare::draw(unsigned int textureID) {
    //backend::getBackend()->clearColorAndBuffersDC(1.0f, 1.0f, 1.0f, 1.0f);
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);
    frameshader->use();
    backend::getBackend()->setTexture(0, textureID, frameshader->GetID(), "screenTexture");


    backend::getBackend()->drawSurface(VAO, 0);


}

