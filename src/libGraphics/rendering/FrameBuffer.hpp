#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <Object.hpp>
#include<RTTI.hpp>



class FrameBuffer : public Object
{
    DECLARE_RTTI
private:

int m_iWidth  , m_iHeight;


public:
unsigned int framebuffer;
unsigned int textureColorbuffer;
unsigned int rbo;

    FrameBuffer(int width, int height);
    ~FrameBuffer();
    void recreate(int width, int height);
    void createFB(int width, int height);
    int getWidth();
    int getHeight();

void use();


};





#endif