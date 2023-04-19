#ifndef SCREENCANVAS_HPP
#define SCREENCANVAS_HPP

#include<FrameBuffer.hpp>
#include<backend.hpp>
#include<Shader.hpp>
#include<Object.hpp>
#include<RTTI.hpp>
//a quad in ND coordinates on top of which to draw a framebuffer
//a screen is also a framebuffer+ other things
//they will be stored in a different class, vector
//they can both be displayed, both have that button, though in different windows
//we differentiate between the two using Rtti
class ScreenCanvas : public Object
{
//so a screencanvas draw, will draw this simple geometry to the memeber framebuffer.
//in order to display this framebuffer in the interface.
DECLARE_RTTI

private:
    static unsigned int VBO;
    static unsigned int VAO;
    /* data */
    static float quadVertices[];
    static FrameBuffer *m_fb;
    static Shader *frameshader;

public:
    ScreenCanvas(/* args */);
    ScreenCanvas(int width, int height);

    void setShader(Shader *shader);
    Shader* getShader();
    
    void draw(float time, float deltaTime);
    void setFrameBuffer(FrameBuffer* fb);
    FrameBuffer* getFrameBuffer();


    ~ScreenCanvas();
    void loadGeometry();
};

#endif
