//the EditorUI will need to access state in the Application class.
#ifndef EDITORUI_HPP
#define EDITORUI_HPP
#include <plog/Log.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiFileBrowser.h"
#include "ImGuiFileBrowser.h"

#include "ImGuizmo.h"


/// @brief EACH METHOD IN THIS CLASS IS RESPONSIBLE FOR RENDERING A UI COMPONENT, THE COMPONENTS WILL ACCES THE APPLICATION CLASS AND OTHER CLASSES IN OTHER TO MODIFY THE STATE OF THE APPLICATION.
///EDITOR SPECIFIC STATE CAN BE PLACED IN THIS CLASS
class Application;
class EditorUI
{
friend class Application;

private:
    /* data */
    static EditorUI * editorUI;
    Application* app;
    static ImGuizmo::OPERATION mCurrentGizmoOperation ;
    static ImGuizmo::MODE mCurrentGizmoMode;
    ImGuiConfigFlags_ keyflag ;
    ImGuiConfigFlags_ mouseflag;
public:
    EditorUI(/* args */);
    ~EditorUI();
    void init_imgui();
    void destroy_imgui();

    void test();
    void render();
    void editTransform();
    /// @brief 
    /// @param app 
    /// @return 
    static EditorUI *getEditorUI(Application *p_app);



};


#include<Application.hpp>
#endif