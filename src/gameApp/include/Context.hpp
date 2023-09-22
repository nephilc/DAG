#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <GLFW/glfw3.h>
#include <string>
#include "ImGuizmo.h"
//#include <glm.hpp>
#include "imgui.h"

enum input_mode
{
EDITOR,
WORLD
};




struct  ApplicationContext{
    bool initialized=false;
    GLFWwindow *m_window;
    ImGuizmo::OPERATION mCurrentGizmoOperation;
    ImGuizmo::MODE mCurrentGizmoMode;
    ImGuiConfigFlags_ keyflag ;
    ImGuiConfigFlags_ mouseflag;
    int m_iWidth, m_iHeight;
    int m_iFrameWidth, m_iFrameHeight;
    int m_iWindowID;
    double m_dTime, m_dDeltaTime;
    float lastX ;
    float lastY ;         
    bool firstMouse;
    input_mode imode;
};

extern ApplicationContext g_ac;



#endif