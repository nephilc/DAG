#include"ScreenCanvas.hpp"


IMPLEMENT_RTTI(ScreenCanvas, Object)

FrameBuffer* ScreenCanvas::m_fb = nullptr;
Shader* ScreenCanvas::frameshader = nullptr;
unsigned int ScreenCanvas::VBO=0;
unsigned int ScreenCanvas::VAO=0;
float ScreenCanvas::quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

ScreenCanvas::ScreenCanvas(): ScreenCanvas(800, 600)
{

}

ScreenCanvas::ScreenCanvas(int width, int height)
{
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
    frameshader = new Shader("shaderPrograms/framebuffer.vs", "shaderPrograms/framebuffer.fs");
    m_fb = new FrameBuffer(800, 600);
    loadGeometry();

}

void ScreenCanvas::setShader(Shader *shader)
{
    frameshader = shader;
}

Shader* ScreenCanvas::getShader()
{
    return frameshader;
}

ScreenCanvas::~ScreenCanvas()
{
}


void ScreenCanvas::setFrameBuffer(FrameBuffer* fb)
{
    m_fb = fb;
}

FrameBuffer* ScreenCanvas::getFrameBuffer()
{
    return m_fb;
}

void ScreenCanvas::loadGeometry()
{
    backend::getBackend()->create2DSquare(&VAO, &VBO, &quadVertices[0], sizeof(quadVertices));
   
}

void ScreenCanvas::draw(float deltaTime) {
    m_fb->use();
    backend::getBackend()->clearColorAndBuffersDC(1.0f, 1.0f, 1.0f, 1.0f);
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);
    frameshader->use();
    backend::getBackend()->drawSurface(VAO, 0);


}

