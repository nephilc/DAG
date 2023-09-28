#ifndef NDCSQUARE_HPP
#define NDCSQUARE_HPP

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
class NDCsquare : public Object
{
//so a screencanvas draw, will draw this simple geometry to the memeber framebuffer.
//in order to display this framebuffer in the interface.
DECLARE_RTTI

private:
    static unsigned int VBO;
    static unsigned int VAO;
    /* data */
    static float quadVertices[];
    static Shader *frameshader;

public:
    NDCsquare(/* args */);

    void setShader(Shader *shader);
    Shader* getShader();
    
    void draw(unsigned int textureID);


    ~NDCsquare();
    void loadGeometry();
};

#endif
