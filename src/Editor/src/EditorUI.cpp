#include<EditorUI.hpp>


//Application *EditorUI::app = nullptr;
EditorUI *EditorUI::editorUI = nullptr;

ImGuizmo::OPERATION EditorUI::mCurrentGizmoOperation(ImGuizmo::ROTATE);
ImGuizmo::MODE EditorUI::mCurrentGizmoMode(ImGuizmo::WORLD);


EditorUI::EditorUI(/* args */)
{
    PLOGI<<"INITIALIZING EDITORUI";
    init_imgui();


}

EditorUI::~EditorUI()
{
        PLOGI<<"EXECUTING EDITORUI DESTRUCTOR";

}

void EditorUI::test()
{
    PLOGE<<editorUI->app->m_acWindowTitle;

}

void EditorUI::render()
{
    bool show_demo_window = true;

    //create the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    //BeginFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    
            editTransform();

}

void EditorUI::editTransform()
{
    ImGui::Begin("window transforms");
    if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
         mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
      ImGui::SameLine();
      if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
         mCurrentGizmoOperation = ImGuizmo::ROTATE;
      ImGui::SameLine();
      if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
         mCurrentGizmoOperation = ImGuizmo::SCALE;

    if (ImGui::RadioButton("WORLD", mCurrentGizmoMode == ImGuizmo::WORLD))
         mCurrentGizmoMode = ImGuizmo::WORLD;
      ImGui::SameLine();
    if (ImGui::RadioButton("LOCAL", mCurrentGizmoMode == ImGuizmo::LOCAL))
         mCurrentGizmoMode = ImGuizmo::LOCAL;
          
    ImGui::End();
}

EditorUI *EditorUI::getEditorUI(Application *p_app)
{
    if(!editorUI)
    {
        assert(p_app!=nullptr);
        editorUI= new EditorUI();
        editorUI->app = p_app;
    }
    return editorUI;
}

void EditorUI::init_imgui()
{
PLOGI<<"INITIALIZING IMGUI";
    
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |=  ImGuiConfigFlags_DockingEnable;
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(app->m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
        PLOGD<<"initialzed IMGUI";
    // Setup Dear ImGui style 
    ImGui::StyleColorsDark();
    PLOGD<<"initialzed style";
    //ImGui::StyleColorsClassic();
    assert(app);
    keyflag = ImGuiConfigFlags_None;
    mouseflag = ImGuiConfigFlags_None;
    io.ConfigFlags |= mouseflag | keyflag;
    
    


}
void EditorUI::destroy_imgui()
{
PLOGI<<"DESTROYING IMGUI";
   ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
 

}
