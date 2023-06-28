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
#include<AssetManager.hpp>
#include<TextEditor.h>
#include <map>

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
    imgui_addons::ImGuiFileBrowser file_dialog;

    //maps a type name to a factory method that creates an object, subtype of Node and adds it to the scene graph.
    //the parametre is the parent Node
    map<string, void(*)(Node*)> NodeFactory;
    AssetManager* m_AM;

    Node* selected;
    TextEditor editor;
    TextEditor::LanguageDefinition lang;
    TextEditor::ErrorMarkers markers;

    bool enableEditing;


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

void showMainMenu();
void updateInputFlags(int mode);
void ImportedModelsWindow(bool* p_open);
void ImportedScenesWindow(bool* p_open);
void ImportedScenesWindowLeft(bool* p_open);
void ImportedScenesWindowRight(bool* p_open);
void DrawTree(Node* scene);
void init_RTTI();
void FramebuffersWindow(bool *p_open);
void  ScreenCanvasesWindow(bool* p_open);
void  TextEditorWindow();


void saveText();

void ObjectProperties(Object *object);
void NodeProperties();
void WorldNodeProperties();
void GeometryNodeProperties();
void AnimatedNodePickModel();
void ModelNodeProperties();
void AnimatedNodeProperties();
void ObjectProperties();
void  EditorProperties();
void KeyMapsTab();
void keyMapsCombo();
void playButton();
void selectableTree();
void createNode();
void  shadersWindow(bool* p_open);
void sceneView(int itextureId,  int *width, int* height, float* view, float* projection, float* idm, float* model);
void ShowPlaceholderObject(const char* prefix, int uid);
void saveSceneButton();
void sceneCombo();
void newSceneButton();
void ImportedStaticModelsWindow(bool* p_open);
void loadAnimationButton(AnimatedNode* AniNode);


};


#include<Application.hpp>
#endif