#include<EditorUI.hpp>
#include <gtc/type_ptr.hpp>


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
    if(file_dialog.showFileDialog("Import scene", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), "*.*"))
    {
        std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
        std::cout << file_dialog.ext << std::endl;              // Access ext separately (For SAVE mode)
        //Do writing of files based on extension here
    }
}

void EditorUI::ImportedModelsWindow(bool* p_open)
{
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("AssetManager Imported models Vector", p_open, ImGuiWindowFlags_MenuBar))
    {
        /*
        //IMGUI_DEMO_MARKER("Examples/Simple layout");
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Close")) *p_open = false;
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        */
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
                    sprintf(text,"objec ID : %i",  selectedM->GetID());

                    ImGui::Text("%s",text);
                    ImGui::Text("NUMBER OF MESHES %i",selectedM->numMeshes);
                    ImGui::Text("NUMBER OF ANIMATIONS %i",selectedM->numAnimations);
                    ImGui::Text("NUMBER OF MATERIALS %i",selectedM->numMaterials);
                    ImGui::Text("NUMBER OF TEXTURES %i, %s",selectedM->numTextures, "(embedded)");
                    ImGui::Text("NUMBER OF LIGHTS %i",selectedM->numLights);
                    ImGui::Text("NUMBER OF CAMERAS %i",selectedM->numCameras);
                    
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

void EditorUI::createNode()
{
    static bool popup = false;
    if(ImGui::Button("+") & Node::selected!=0)   ImGui::OpenPopup("my_select_popup");


    if (ImGui::BeginPopup("my_select_popup"/*,  NULL*/, ImGuiWindowFlags_AlwaysAutoResize))
    {
            ImGui::Text("Aquarium");
            ImGui::Separator();
            if(ImGui::Button("add", ImVec2(120, 0))) ImGui::CloseCurrentPopup();
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    
    }

}


void EditorUI::ImportedScenesWindow(bool* p_open)
{
    static float translation[3];
    static float rotation[3];
    static float scale[3];
    static float angle;

    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("AssetManager Imported scenes Vector", p_open, ImGuiWindowFlags_MenuBar))
    {
        createNode();
        // Left
        static int selected = 0;

        {
            ImGui::BeginChild("left pane", ImVec2(ImGui::GetWindowSize().x/2, 0), true); // Leave room for 1 line below us

            m_AM->scene->DrawTree();
         
            
            ImGui::EndChild();

        }
        ImGui::SameLine();
        // Right
        {
            ImGui::BeginGroup();//this child window will scroll on it's own
            ImGui::BeginChild("item view1", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            
            if(Node::selected) ImGui::Text("MyObject: %s", Node::selected->GetName().c_str());
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {
               //do this kind of thing
               //if(Node::selected->GetType().isDerived(ParentNode::TYPE)) DISPLAY Section related to that parent
                if (ImGui::BeginTabItem("Scene Details"))
                {
                    if(Node::selected){
                    char text[128];
                    //string text = string("object id") + string("%i", m_AM->getModels()[selected]->GetID()); 
                    sprintf(text,"object ID : %i",  Node::selected->GetID());
                    
                    ImGui::Text("%s",text);
                    ImGui::Text("Node type %s", Node::selected->GetType().GetName().c_str());

                    translation[0] = Node::selected->getTranslation().x;  
                    translation[1] = Node::selected->getTranslation().y;  
                    translation[2] = Node::selected->getTranslation().z;  

                    rotation[0] = Node::selected->getRotationAxis().x;  
                    rotation[1] = Node::selected->getRotationAxis().y;  
                    rotation[2] = Node::selected->getRotationAxis().z;  

                    scale[0] = Node::selected->getScale().x;  
                    scale[1] = Node::selected->getScale().y;  
                    scale[2] = Node::selected->getScale().z;  

                    angle = Node::selected->getRotationAngle();
                    if(ImGui::InputFloat3("translation",translation))
                    {
                     Node::selected->setTranslation(translation);  
                    }

                    if(ImGui::InputFloat("rotation angle",&angle))
                    {
                     Node::selected->setRotationAngle(angle);  
                    }

                    if(ImGui::InputFloat3("rotation axis",rotation))
                    {
                     Node::selected->setRotationAxis(rotation);  
                    }

                    if(ImGui::InputFloat3("Scale",scale))
                    {
                     Node::selected->setScale(scale);  
                    }
                    ImGui::Text("Node's transform");
                    for(int i = 0; i<=3; ++i)
                    {
                        for(int j = 0; j <=3; ++j)
                        {
                            ImGui::Text("%f", Node::selected->getWorldTransform()[i][j]);
                            ImGui::SameLine();
                        }
                        ImGui::NewLine();

                    }
                    glm::vec4 worldx, worldy, worldz, world;
                    glm::mat4 parentInverse = glm::mat4(1.0f);
                    if(Node::selected->m_parent!=0)
                        parentInverse = glm::inverse(Node::selected->m_parent->m_world);
                    worldx = parentInverse * glm::vec4(1,0,0,0);
                    worldy = parentInverse * glm::vec4(0,1,0,0);
                    worldz = parentInverse * glm::vec4(0,0,1,0);
                    
                    ImGui::Text("the worldx in the parent frame");
  
                      for(int j = 0; j <=3; ++j)
                        {
                            ImGui::Text("%f", worldx[j]);
                            ImGui::SameLine();
                        }
                        ImGui::NewLine();
ImGui::Text("the worldy in the parent frame");
  
                      for(int j = 0; j <=3; ++j)
                        {
                            ImGui::Text("%f", worldy[j]);
                            ImGui::SameLine();
                        }
                        ImGui::NewLine();
ImGui::Text("the worldz in the parent frame");
  
                      for(int j = 0; j <=3; ++j)
                        {
                            ImGui::Text("%f", worldz[j]);
                            ImGui::SameLine();
                        }
                        ImGui::NewLine();

                    //shaders 
                    static int item_current_idx = 0; // Here we store our selection data as an index.
                    vector<Shader*> shaders = m_AM->getShaders();
                    if (ImGui::BeginListBox("listbox 1"))
                    {
                    for (int n = 0; n < shaders.size(); n++)
                        {
                            //item_current_idx = n;

                            const bool is_selected = (Node::selected->getShader() == shaders[n]);
                            if (ImGui::Selectable(shaders[n]->GetName().c_str(), is_selected))
                                Node::selected->setShader(shaders[n]);

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndListBox();
                    }
                    //end of shaders


                    }
                    ImGui::EndTabItem();

                }
                if (ImGui::BeginTabItem("Description"))
                {
                    if(Node::selected){
                    ImGui::TextWrapped("Scene Node");
                    }
                    ImGui::EndTabItem();

                }
               
                ImGui::EndTabBar();
            }
            
            ImGui::EndChild();
            
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
        selectedS = vlshaders[selected];
        // Right
        {
            ImGui::BeginGroup();//this child window will scroll on it's own
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            ImGui::Text("Object Name: %s", selectedS->GetName().c_str());
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {
               
                if (ImGui::BeginTabItem("Shader Details"))
                {
                    char text[128];
                    //string text = string("object id") + string("%i", m_AM->getModels()[selected]->GetID()); 
                    sprintf(text,"objec ID : %i",  selectedS->GetID());
                    ImGui::Text(" %s", text);
                    ImGui::Separator();
                    if(ImGui::Button("Reload", ImVec2(100, 50)))
                    {
                        selectedS->reload();
                    }
                    
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Description"))
                {
                    ImGui::TextWrapped("One can reload shaders");
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
ImGui::Begin("OpenGL Texture Window",  &open);
//ImGui::Text("pointer = %p", textureColorbuffer);
//ImGui::Text("size = %d x %d", m_iWidth, m_iHeight);

//int frame_dims[2]; 

*width = (float)ImGui::GetWindowWidth();
*height = (float)ImGui::GetWindowHeight();

//m_iFrameWidth = frame_dims[0];
//m_iFrameHeight = frame_dims[1];

ImGui::Image((void*)(intptr_t)app->m_FB->textureColorbuffer, ImVec2(*width, *height), ImVec2(0, 1), ImVec2(1, 0));






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

  

    
    ImGuizmo::DrawGrid(view, projection, idm, 100.f);

   //ImGuizmo::DrawCubes(view, projection, model, 1);
   //ImGuizmo::Manipulate(view, projection, mCurrentGizmoOperation, mCurrentGizmoMode, model, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);
//manipulate is what draws the gizmo
//glm::mat4 current = 
if(Node::selected !=0)
{
    
         glm::mat4 deltaMatrix;
         glm::vec3 position, rotation, scale;

    if (mCurrentGizmoMode == ImGuizmo::WORLD)
{

    if(ImGuizmo::Manipulate(view, projection, mCurrentGizmoOperation, ImGuizmo::WORLD, &(Node::selected->m_world)[0][0], &(deltaMatrix)[0][0], useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL) )
        {
        Node::selected->manipulated = true;
        ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(deltaMatrix), 
                                           glm::value_ptr(position), 
                                           glm::value_ptr(rotation), 
                                           glm::value_ptr(scale));
        glm::vec4 worldx, worldy, worldz, world, newrot;
        glm::vec4 worldx2, worldy2, worldz2;

        //Node::selected->m_local = glm::scale(Node::selected->m_local, scale);
        if(mCurrentGizmoOperation == ImGuizmo::TRANSLATE){
        glm::mat4 parentInverse = glm::mat4(1.0f);
        if(Node::selected->m_parent!=0)
        parentInverse = glm::inverse(Node::selected->m_parent->m_world);
        worldx = parentInverse * glm::vec4(1,0,0,0);
        worldy = parentInverse * glm::vec4(0,1,0,0);
        worldz = parentInverse * glm::vec4(0,0,1,0);
        
        world = worldx + worldy + worldz;
        glm::vec4 positionInParent = parentInverse * glm::vec4(position, 0);

        PLOGE<<"position in parent is "<<positionInParent.x<<" "<<positionInParent.y<<" "<<positionInParent.z;
        Node::selected->m_LocalTranslation = glm::translate(Node::selected->m_LocalTranslation, position);
        Node::selected->m_localTranslationMat = glm::translate(Node::selected->m_localTranslationMat, glm::vec3(positionInParent));
        
        Node::selected->updateTransforms();
        }
        if(mCurrentGizmoOperation == ImGuizmo::ROTATE)
        {
            //always compute rotations using this translation matrix
            //glm::mat4 thisRotation = glm::mat4(1.0f);
            //thisRotation = glm::rotate(thisRotation,glm::radians(rotation[0]), glm::vec3(1, 0 ,0) );
            //thisRotation = glm::rotate(thisRotation ,glm::radians(rotation[1]), glm::vec3(0, 1, 0) );
            //thisRotation = glm::rotate(thisRotation ,glm::radians(rotation[2]), glm::vec3(0, 0, 1) );
            //Node::selected->m_localRotationMat = glm::rotate(Node::selected->m_localRotationMat,glm::radians(rotation[0]), glm::vec3(worldx2) );
            float angle = glm::radians(glm::length(rotation));
            glm::mat4 parentInverse2 = glm::inverse(Node::selected->m_world);
            worldx2 = parentInverse2 * glm::vec4(1,0,0,0);
            worldy2 = parentInverse2 * glm::vec4(0,1,0,0);
            worldz2 = parentInverse2 * glm::vec4(0,0,1,0);

            //newrot = inversePa
            Node::selected->m_localRotationMat = glm::rotate(Node::selected->m_localRotationMat,glm::radians(rotation[0]), glm::vec3(worldx2));
            Node::selected->m_localRotationMat = glm::rotate(Node::selected->m_localRotationMat,glm::radians(rotation[1]), glm::vec3(worldy2));
            Node::selected->m_localRotationMat = glm::rotate(Node::selected->m_localRotationMat,glm::radians(rotation[2]), glm::vec3(worldz2) );

            Node::selected->updateTransforms();//reset the translation matrix

            //Node::selected->m_localRotationMat = Node::selected->m_localRotationMat * thisRotation; 
            //Node::selected->updateTransforms();

            
        }
        //Node::selected->m_local = glm::rotate(Node::selected->m_local,glm::radians(rotation[0]), glm::vec3(1, 0, 0) );
        //Node::selected->m_local = glm::rotate(Node::selected->m_local,glm::radians(rotation[1]), glm::vec3(0, 1, 0) );
        //Node::selected->m_local = glm::rotate(Node::selected->m_local,glm::radians(rotation[2]), glm::vec3(0, 0, 1) );
        PLOGD<<"manipulated";
        }
    else Node::selected->manipulated = false;

}
    if (mCurrentGizmoMode == ImGuizmo::LOCAL)
{
    if(ImGuizmo::Manipulate(view, projection, mCurrentGizmoOperation, ImGuizmo::LOCAL, &(Node::selected->m_WorldTranslation)[0][0], &(deltaMatrix)[0][0],useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL))
        {Node::selected->manipulated = true;
    Node::selected->manipulated = true;
        ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(deltaMatrix), 
                                           glm::value_ptr(position), 
                                           glm::value_ptr(rotation), 
                                           glm::value_ptr(scale));
        PLOGD<<position.x<<position.y<<position.z;
        //Node::selected->m_local = glm::scale(Node::selected->m_local, scale);
        Node::selected->m_local =glm::translate(Node::selected->m_local, position);
        PLOGD<<"LOCAL MANIPULATED";
        }
    else Node::selected->manipulated = false;
}

}


ImGuizmo::ViewManipulate(view, camDistance, ImVec2(viewManipulateRight - 128, viewManipulateTop), ImVec2(128, 128), 0x10101010);









ImGui::End();


}

