#ifndef SCREENCANVAS_HPP
#define SCREENCANVAS_HPP
//a quad in ND coordinates on top of which to draw a framebuffer
//a screen is also a framebuffer+ other things
//they will be stored in a different class, vector
//they can both be displayed, both have that button, though in different windows
//we differentiate between the two using Rtti
class ScreenCanvas
{
private:
    /* data */
public:
    ScreenCanvas(/* args */);
    ~ScreenCanvas();
};

#endif