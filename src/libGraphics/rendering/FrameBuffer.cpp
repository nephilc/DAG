#include "FrameBuffer.hpp"


#include <glad/glad.h>
#include <plog/Log.h>



FrameBuffer::FrameBuffer(int width, int height):m_iWidth(width), m_iHeight(height)
{
    createFB(width, height);
 
}

FrameBuffer::~FrameBuffer()
{
}


void FrameBuffer::createFB(int width, int height)
{

    glGenFramebuffers(1, &this->framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

    glGenTextures(1, &this->textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, this->textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width  , height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);  

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	PLOGD << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
    else PLOGD << "FRAMEBUFFER CREATION WAS A SUCCES";
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
int FrameBuffer::getWidth()
{
    return m_iWidth;
}
int FrameBuffer::getHeight()
{
    return m_iHeight;
}
void FrameBuffer::use()
{
glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

}

void FrameBuffer::recreate(int width, int height)
{
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &textureColorbuffer);
    glDeleteRenderbuffers(1, &rbo);
    createFB(width, height);
    PLOGD<<"recreated fb";
    PLOGD<<width <<height;
    PLOGD<<framebuffer;
    PLOGD<<textureColorbuffer;
    PLOGD<<rbo;
    
    
}
