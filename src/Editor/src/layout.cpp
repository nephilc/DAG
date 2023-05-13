#include<EditorUI.hpp>
#include <gtc/type_ptr.hpp>

void EditorUI::saveText()
{
    auto textToSave = editor.GetText();
    PLOGD << textToSave;
    std::ofstream file("shaderPrograms/framebuffer.fs"); // create file object
    if (file.is_open()) { // check if file is open
        file << textToSave;
        file.close(); // close file
    }
    else {
        std::cerr << "Unable to open file." << std::endl;
    }


}

void EditorUI::showMainMenu()
{
    bool open = false, save = false;
    if(ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Import"))
        {
            if (ImGui::MenuItem("Import model", NULL))
                open = true;
        if (ImGui::MenuItem("Import scene", NULL))
                save = true;
        ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            static bool s_enableEditing= false;
            if (ImGui::Checkbox("Enable Editing", &s_enableEditing))
                enableEditing = s_enableEditing;
            if (ImGui::MenuItem("Save", "Ctrl-S") || (ImGui::GetIO().KeyCtrl && ImGui::IsKeyPressed('S')))
            {
                saveText();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    
    //Remember the name to ImGui::OpenPopup() and showFileDialog() must be same...
    if(open)
        ImGui::OpenPopup("Import model");
    if(save)
        ImGui::OpenPopup("Import scene");
        
    /* Optional third parameter. Support opening only compressed rar/zip files. 
     * Opening any other file will show error, return false and won't close the dialog.
     */
    if(file_dialog.showFileDialog("Import model", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), "*.*"))
    {
        m_AM->loadModel(file_dialog.selected_path, file_dialog.selected_fn);
        std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
    }
    if(file_dialog.showFileDialog("Import scene", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".xdg"))
    {
        std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
        std::cout << file_dialog.ext << std::endl;  
        m_AM->loadScene(file_dialog.selected_path);

        
        // Access ext separately (For SAVE mode)
        //Do writing of files based on extension here
    }
}

void EditorUI::ImportedModelsWindow(bool* p_open)
{
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("AssetManager Imported models Vector", p_open, ImGuiWindowFlags_MenuBar))
    {
        // Left
        static int selected = 0;
        Model* selectedM;
        {
            Model* model;
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < m_AM->getModels().size(); i++)
            {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                model = m_AM->getModels()[i];
                char label[128];
                sprintf(label, "%s", model->GetName().c_str());
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();
        selectedM = m_AM->getModels()[selected];
        // Right
        {
            ImGui::BeginGroup();//this child window will scroll on it's own
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            ImGui::Text("MyObject: %s", selectedM->GetName().c_str());
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {

                if (ImGui::BeginTabItem("Model Details"))
                {
                    char text[128];
                    //string text = string("object id") + string("%i", m_AM->getModels()[selected]->GetID()); 
                    sprintf(text, "objec ID : %i", selectedM->GetID());

                    ImGui::Text("%s", text);
                    ImGui::Text("NUMBER OF MESHES %i", selectedM->numMeshes);
                    ImGui::Text("NUMBER OF ANIMATIONS %i", selectedM->numAnimations);
                    ImGui::Text("NUMBER OF MATERIALS %i", selectedM->numMaterials);
                    ImGui::Text("NUMBER OF TEXTURES %i, %s", selectedM->numTextures, "(embedded)");
                    ImGui::Text("NUMBER OF LIGHTS %i", selectedM->numLights);
                    ImGui::Text("NUMBER OF CAMERAS %i", selectedM->numCameras);

                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Description"))
                {
                    ImGui::TextWrapped("A scene is loaded as single model");
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            /*
            if (ImGui::Button("Revert")) {}
            ImGui::SameLine();
            if (ImGui::Button("Save")) {}
            */
            ImGui::EndGroup();
        }
    }
    ImGui::End();
}

void EditorUI::ImportedStaticModelsWindow(bool* p_open)
{
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("AssetManager Imported Static models Vector", p_open, ImGuiWindowFlags_MenuBar))
    {
        // Left
        static int selected = 0;
        Model* selectedM;
        {
            Model* model;
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < m_AM->getModels().size(); i++)
            {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                model = m_AM->getModels()[i];
                char label[128];
                sprintf(label, "%s", model->GetName().c_str());
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();
        selectedM = m_AM->getModels()[selected];
        // Right
        {
            ImGui::BeginGroup();//this child window will scroll on it's own
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            ImGui::Text("MyObject: %s", selectedM->GetName().c_str());
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {

                if (ImGui::BeginTabItem("Model Details"))
                {
                    char text[128];
                    //string text = string("object id") + string("%i", m_AM->getModels()[selected]->GetID()); 
                    sprintf(text, "objec ID : %i", selectedM->GetID());

                    ImGui::Text("%s", text);
                    ImGui::Text("NUMBER OF MESHES %i", selectedM->numMeshes);
                    ImGui::Text("NUMBER OF ANIMATIONS %i", selectedM->numAnimations);
                    ImGui::Text("NUMBER OF MATERIALS %i", selectedM->numMaterials);
                    ImGui::Text("NUMBER OF TEXTURES %i, %s", selectedM->numTextures, "(embedded)");
                    ImGui::Text("NUMBER OF LIGHTS %i", selectedM->numLights);
                    ImGui::Text("NUMBER OF CAMERAS %i", selectedM->numCameras);

                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Description"))
                {
                    ImGui::TextWrapped("A scene is loaded as single model");
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            /*
            if (ImGui::Button("Revert")) {}
            ImGui::SameLine();
            if (ImGui::Button("Save")) {}
            */
            ImGui::EndGroup();
        }
    }
    ImGui::End();
}


void  EditorUI::shadersWindow(bool* p_open)
{   

    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("AssetManager Imported shaders Vector", p_open, ImGuiWindowFlags_MenuBar))
    {
        vector<Shader*> vlshaders = m_AM->getShaders();
        // Left
        static int selected = 0;
        Shader* selectedS;
        {
            Shader* shader;
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < vlshaders.size(); i++)
            {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                shader = vlshaders[i];
                char label[128];
                sprintf(label, "%s", shader->GetName().c_str());
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();
        if(vlshaders.size()>0)
        selectedS = vlshaders[selected];
        // Right
        if(vlshaders.size()>0)
        {
            ImGui::BeginGroup();//this child window will scroll on it's own
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            ImGui::Text("Object Name: %s", selectedS->GetName().c_str());
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {
               
                if (ImGui::BeginTabItem("Shader Details"))
                {
                    ObjectProperties(selectedS);
                    ImGui::Separator();
                    if(ImGui::Button("Reload", ImVec2(100, 50)))
                    {
                        selectedS->reload();
                    }
                    
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            /*
            if (ImGui::Button("Revert")) {}
            ImGui::SameLine();
            if (ImGui::Button("Save")) {}
            */
            ImGui::EndGroup();
        }
    }
    ImGui::End();
}
void  EditorUI::FramebuffersWindow(bool* p_open)
{   

    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("AssetManager Created Framebuffers Vector", p_open, ImGuiWindowFlags_MenuBar))
    {
        vector<FrameBuffer*> vlfbs = m_AM->getFrameBuffers();
        // Left
        static int selected = 0;
        FrameBuffer* selectedfb;
        {
            FrameBuffer* fb;
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < vlfbs.size(); i++)
            {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                fb = vlfbs[i];
                char label[128];
                sprintf(label, "%s", fb->GetName().c_str());
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();
        if(vlfbs.size()>0)
        selectedfb = vlfbs[selected];
        // Right
                if(vlfbs.size()>0)

        {
            ImGui::BeginGroup();//this child window will scroll on it's own
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            ImGui::Text("Object Name: %s", selectedfb->GetName().c_str());
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {
               
                if (ImGui::BeginTabItem("FB Details"))
                {
                    ObjectProperties(selectedfb);
                    ImGui::Separator();
                    if(ImGui::Button("Show in Window", ImVec2(100, 50)))
                    {
                        m_AM->makeBufferCurrent(selectedfb);
                        //selectedfb->reload();
                    }
                    
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            /*
            if (ImGui::Button("Revert")) {}
            ImGui::SameLine();
            if (ImGui::Button("Save")) {}
            */
            ImGui::EndGroup();
        }
    }
    ImGui::End();
}


void  EditorUI::ScreenCanvasesWindow(bool* p_open)
{

    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("AssetManager Created ScreenCanvases Vector", p_open, ImGuiWindowFlags_MenuBar))
    {
        vector<ScreenCanvas*> vlscs = m_AM->getScreenCanvases();
        // Left
        static int selected = 0;
        ScreenCanvas* selectedsc;
        {
            ScreenCanvas* sc;
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < vlscs.size(); i++)
            {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                sc = vlscs[i];
                char label[128];
                sprintf(label, "%s", sc->GetName().c_str());
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();
        if (vlscs.size() > 0)
            selectedsc = vlscs[selected];
        // Right
        if (vlscs.size() > 0)

        {
            ImGui::BeginGroup();//this child window will scroll on it's own
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            ImGui::Text("Object Name: %s", selectedsc->GetName().c_str());
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {

                if (ImGui::BeginTabItem("SC Details"))
                {
                    ObjectProperties(selectedsc);
                    ImGui::Separator();
                    if (ImGui::Button("Show in Window", ImVec2(100, 50)))
                    {
                        m_AM->makeBufferCurrent(selectedsc->getFrameBuffer());
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("reload shader", ImVec2(100, 50)))
                    {
                        selectedsc->getShader()->reload();
                    }
                    //#######################################################
                    //##############change the shader vs and fs shader path

                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            /*
            if (ImGui::Button("Revert")) {}
            ImGui::SameLine();
            if (ImGui::Button("Save")) {}
            */
            ImGui::EndGroup();
        }
    }
    ImGui::End();
}


void EditorUI::ShowPlaceholderObject(const char* prefix, int uid)
{
    // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
    ImGui::PushID(uid);

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
    bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
    ImGui::Text("my sailor is rich");//we could also use a selectable
    //we can mix tree nodes and selectable to point ot different kinds of objects.

    if (node_open)//only display this stuff if the node is open, we will have to display nodes recursively.
    {
        static float placeholder_members[8] = { 0.0f, 0.0f, 1.0f, 3.1416f, 100.0f, 999.0f };
        for (int i = 0; i < 8; i++)
        {
            ImGui::PushID(i); // Use field index as identifier.
            if (i < 2)
            {
                //ShowPlaceholderObject("Child", 424242);
            }
            else
            {
                // Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
                ImGui::TreeNodeEx("Field", flags, "Field_%d", i);

               }
            ImGui::PopID();
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
}

void EditorUI::selectableTree()
{
     static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    static int selection_mask = (1 << 2);
            int node_clicked = -1;//we use this variable to update selection mask after the loop.
            for (int i = 0; i < 6; i++)
            {
                // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
                // To alter selection we use IsItemClicked() && !IsItemToggledOpen(), so clicking on an arrow doesn't alter selection.
                ImGuiTreeNodeFlags node_flags = base_flags;
                const bool is_selected = (selection_mask & (1 << i)) != 0;
                if (is_selected)
                    node_flags |= ImGuiTreeNodeFlags_Selected;
                if (i < 3)
                {
                    // Items 0..2 are Tree Node
                    bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Node %d", i);
                    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                        node_clicked = i;
                        //here we can set a pointer to the object represented by this node.
                    if (node_open)
                    {
                        ImGui::BulletText("Blah blah\nBlah Blah");
                        ImGui::TreePop();
                    }
                }
                else
                {
                    // Items 3..5 are Tree Leaves
                    // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
                    // use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
                    node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
                    ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
                    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                        node_clicked = i;
                }
            }
            if (node_clicked != -1)
            {
                // Update selection state
                // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
                if (ImGui::GetIO().KeyCtrl)
                    selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
                else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
                    selection_mask = (1 << node_clicked);           // Click to single-select
            }
        

}

void EditorUI::sceneView(int itextureId, int *width, int* height, float* view, float* projection, float* idm, float* model)
{
bool open = true;
ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
ImGui::Begin("OpenGL Texture Window",  &open);
//ImGui::Text("pointer = %p", textureColorbuffer);
//ImGui::Text("size = %d x %d", m_iWidth, m_iHeight);

//int frame_dims[2]; 
//static int previousWidth, previousHeight;
*width = (float)ImGui::GetWindowWidth();//
*height = (float)ImGui::GetWindowHeight();//
ImVec2 windowSize = ImGui::GetContentRegionAvail();
//m_iFrameWidth = frame_dims[0];
//m_iFrameHeight = frame_dims[1];
//fit the image to the window
//it is the image object that causes the iverflow, it needs to be smaller than the windows dimensions
//ImGui::Image((void*)(intptr_t)app->m_FB->textureColorbuffer, ImVec2(float(app->m_FB->getWidth()), (app->m_FB->getHeight())), ImVec2(0, 1), ImVec2(1, 0));
ImGui::Image((void*)(intptr_t)m_AM->getCurrentFrameBuffer()->textureColorbuffer, windowSize, ImVec2(0, 1), ImVec2(1, 0));


//playButton();



float camDistance = 8.f;
bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
int selected_vertex = 0;
bool hovering_imgui = false;

static bool useSnap = false;
static float snap[3] = { 1.f, 1.f, 1.f };
static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
static bool boundSizing = false;
static bool boundSizingSnap = false;

  //mCurrentGizmoOperation = ImGuizmo::TRANSLATE;

   ImGuiIO& io = ImGui::GetIO();
    float viewManipulateRight = ImGui::GetWindowPos().x+*width;
    float viewManipulateTop = ImGui::GetWindowPos().y;
    static ImGuiWindowFlags gizmoWindowFlags = 0;
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();
   

    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, *width, *height);//this method is essential, passes the display size to imguizmo


    //ImGuizmo::Enable(true);
    //ImGuizmo::Manipulate(&view[0][0], &projection[0][0], mCurrentGizmoOperation, mCurrentGizmoMode, &model[0][0], NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);
    //ImGui::InputFloat3("Snap", &snap[0]);

  

    
    //ImGuizmo::DrawGrid(view, projection, idm, 100.f);

   //ImGuizmo::DrawCubes(view, projection, model, 1);
   //ImGuizmo::Manipulate(view, projection, mCurrentGizmoOperation, mCurrentGizmoMode, model, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);
//manipulate is what draws the gizmo
//glm::mat4 current = 
if(selected !=0)
{
    
         glm::mat4 deltaMatrix;
         glm::vec3 position, rotation, scale;
         

    if (mCurrentGizmoMode == ImGuizmo::WORLD)
{

    if(ImGuizmo::Manipulate(view, projection, mCurrentGizmoOperation, ImGuizmo::WORLD, &(selected->m_world)[0][0], &(deltaMatrix)[0][0], useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL) )
        {
        //selected->manipulated = true;
        ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(deltaMatrix), 
                                           glm::value_ptr(position), 
                                           glm::value_ptr(rotation), 
                                           glm::value_ptr(scale));
        glm::vec4 worldx, worldy, worldz, world, newrot;
        glm::vec4 worldx2, worldy2, worldz2;

        //selected->m_local = glm::scale(selected->m_local, scale);
        if(mCurrentGizmoOperation == ImGuizmo::TRANSLATE){
        glm::mat4 parentInverse = glm::mat4(1.0f);
        if(selected->m_parent!=0)
        parentInverse = glm::inverse(selected->m_parent->m_world);
        worldx = parentInverse * glm::vec4(1,0,0,0);
        worldy = parentInverse * glm::vec4(0,1,0,0);
        worldz = parentInverse * glm::vec4(0,0,1,0);
        
        world = worldx + worldy + worldz;
        glm::vec4 positionInParent = parentInverse * glm::vec4(position, 0);

        PLOGE<<"position in parent is "<<positionInParent.x<<" "<<positionInParent.y<<" "<<positionInParent.z;
        //selected->m_LocalTranslation = glm::translate(selected->m_LocalTranslation, position);
        selected->m_localTranslationMat = glm::translate(selected->m_localTranslationMat, glm::vec3(positionInParent));
        
        selected->updateTransforms();
        }
        if(mCurrentGizmoOperation == ImGuizmo::ROTATE)
        {
            //always compute rotations using this translation matrix
            //glm::mat4 thisRotation = glm::mat4(1.0f);
            //thisRotation = glm::rotate(thisRotation,glm::radians(rotation[0]), glm::vec3(1, 0 ,0) );
            //thisRotation = glm::rotate(thisRotation ,glm::radians(rotation[1]), glm::vec3(0, 1, 0) );
            //thisRotation = glm::rotate(thisRotation ,glm::radians(rotation[2]), glm::vec3(0, 0, 1) );
            //selected->m_localRotationMat = glm::rotate(selected->m_localRotationMat,glm::radians(rotation[0]), glm::vec3(worldx2) );
            float angle = glm::radians(glm::length(rotation));
            glm::mat4 parentInverse2 = glm::inverse(selected->m_world);
            worldx2 = parentInverse2 * glm::vec4(1,0,0,0);
            worldy2 = parentInverse2 * glm::vec4(0,1,0,0);
            worldz2 = parentInverse2 * glm::vec4(0,0,1,0);

            //newrot = inversePa
            selected->m_localRotationMat = glm::rotate(selected->m_localRotationMat,glm::radians(rotation[0]), glm::vec3(worldx2));
            selected->m_localRotationMat = glm::rotate(selected->m_localRotationMat,glm::radians(rotation[1]), glm::vec3(worldy2));
            selected->m_localRotationMat = glm::rotate(selected->m_localRotationMat,glm::radians(rotation[2]), glm::vec3(worldz2) );

            selected->updateTransforms();//reset the translation matrix

            //selected->m_localRotationMat = selected->m_localRotationMat * thisRotation; 
            //selected->updateTransforms();

            
        }
        //selected->m_local = glm::rotate(selected->m_local,glm::radians(rotation[0]), glm::vec3(1, 0, 0) );
        //selected->m_local = glm::rotate(selected->m_local,glm::radians(rotation[1]), glm::vec3(0, 1, 0) );
        //selected->m_local = glm::rotate(selected->m_local,glm::radians(rotation[2]), glm::vec3(0, 0, 1) );
        PLOGD<<"manipulated";
        }
//    else selected->manipulated = false;

}
    if (mCurrentGizmoMode == ImGuizmo::LOCAL)
{
    if(ImGuizmo::Manipulate(view, projection, mCurrentGizmoOperation, ImGuizmo::LOCAL, &(selected->m_world)[0][0], &(deltaMatrix)[0][0],useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL))
        {

        //selected->manipulated = true;
        ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(deltaMatrix), 
                                           glm::value_ptr(position), 
                                           glm::value_ptr(rotation), 
                                           glm::value_ptr(scale));
        PLOGD<<position.x<<position.y<<position.z;
        //selected->m_local = glm::scale(selected->m_local, scale);
        selected->m_local =glm::translate(selected->m_local, position);
        PLOGD<<"LOCAL MANIPULATED";
        }
    //else selected->manipulated = false;
}

}


ImGuizmo::ViewManipulate(view, camDistance, ImVec2(viewManipulateRight - 128, viewManipulateTop), ImVec2(128, 128), 0x10101010);









ImGui::End();
ImGui::PopStyleVar(2);

}


void  EditorUI::TextEditorWindow()
{
    if (ImGui::GetIO().KeyCtrl && ImGui::IsKeyPressed('S'))
    {
        saveText();
    }
    else if (ImGui::GetIO().KeyCtrl && ImGui::IsKeyPressed('R')) {
        saveText();
        m_AM->getScreenCanvas("sc1")->getShader()->reload();
    }

    editor.Render("TextEditor");




}

void  EditorUI::EditorProperties()
{

    static bool p_open = true;
        ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
        ImGui::Begin("EDITOR PROPERTIES", &p_open);
        static float speed = app->camera->MovementSpeed;
        if (ImGui::InputFloat("Editor Camera speed", &speed))
            app->camera->MovementSpeed = speed;
        ImGui::SameLine();
        ImGui::Text("m/s");
        if (ImGui::CollapsingHeader("KeyBoard -> Action map")) {

            for (std::string& key : m_AM->keyBoardVector)
            {
                //ImGui::Text("%s", key.c_str());
                //ImGui::SameLine();
                //ImGui::Text(m_AM->KeyboardActionMap[key]->GetName().c_str());
                //get the coorect index here or create the inverse map
                static int item_current_idx = 0; // Here we store our selection data as an index.
                const char* combo_preview_value = m_AM->KeyboardActionMap[key]->GetName().c_str();  // Pass in the preview value visible before opening the combo (it could be anything)
                if (ImGui::BeginCombo(string(key + " ======> ").c_str(), combo_preview_value, ImGuiComboFlags_NoPreview))
                {
                    for (int n = 0; n < m_AM->KeyActionsVector.size(); n++)
                    {
                        if (m_AM->KeyActionsVector[n] == m_AM->KeyboardActionMap[key]) item_current_idx = n;
                        else item_current_idx = n+1;
                        const bool is_selected = (item_current_idx == n);
                        if (ImGui::Selectable(m_AM->KeyActionsVector[n]->GetName().c_str(), is_selected)) {
                            item_current_idx = n;
                            m_AM->KeyboardActionMap[key] = m_AM->KeyActionsVector[n];
                            PLOGE << m_AM->KeyboardActionMap[key]->GetName();
                        }

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                    ImGui::SameLine();
                    ImGui::Text(m_AM->KeyboardActionMap[key]->GetName().c_str());

                }
                else {
                    ImGui::SameLine();
                    ImGui::Text(m_AM->KeyboardActionMap[key]->GetName().c_str());
                }

            }
        }
        if (ImGui::CollapsingHeader("Mouse -> Action map")) {

            for (std::string& key : m_AM->MouseVector)
            {
                //ImGui::Text("%s", key.c_str());
                //ImGui::SameLine();
                //ImGui::Text(m_AM->KeyboardActionMap[key]->GetName().c_str());
                //get the coorect index here or create the inverse map
                static int item_current_idx = 0; // Here we store our selection data as an index.
                const char* combo_preview_value = m_AM->MouseActionMap[key]->GetName().c_str();  // Pass in the preview value visible before opening the combo (it could be anything)
                if (ImGui::BeginCombo(string(key + " ======> ").c_str(), combo_preview_value, ImGuiComboFlags_NoPreview))
                {
                    for (int n = 0; n < m_AM->MouseActionsVector.size(); n++)
                    {
                        if (m_AM->MouseActionsVector[n] == m_AM->MouseActionMap[key]) item_current_idx = n;
                        else item_current_idx = n + 1;
                        const bool is_selected = (item_current_idx == n);
                        if (ImGui::Selectable(m_AM->MouseActionsVector[n]->GetName().c_str(), is_selected)) {
                            item_current_idx = n;
                            m_AM->MouseActionMap[key] = m_AM->MouseActionsVector[n];
                            PLOGE << m_AM->MouseActionMap[key]->GetName();
                        }

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                    ImGui::SameLine();
                    ImGui::Text(m_AM->MouseActionMap[key]->GetName().c_str());

                }
                else {
                    ImGui::SameLine();
                    ImGui::Text(m_AM->MouseActionMap[key]->GetName().c_str());
                }

            }
        }
        //add another one for game pads
    ImGui::End();
}