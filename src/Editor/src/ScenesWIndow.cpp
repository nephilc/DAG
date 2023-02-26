#include<EditorUI.hpp>
#include <gtc/type_ptr.hpp>










//we dont have a problem with instancing, since it is built into the engine from day1
//for example, a ModelNode will use a model from thos loaded by the aset manager; on creatin it will use the default model
//we will create defaults with the method createDefault(type, parent)
//we are not reusing the nodes, we are resusing data, as it should be done. And we have some default data.
void EditorUI::createNode()
{
    static bool popup = false;
    if(ImGui::Button("+") & selected!=0)   ImGui::OpenPopup("my_select_popup");


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


void EditorUI::DrawTree(Node* scene) {
    static Node *dragsource2 = 0;
    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth ;
    if (selected==scene) {
        node_flags |= ImGuiTreeNodeFlags_Selected;
    }
    if(dragsource2 ==scene)  ImGui::SetNextItemOpen(false);
    bool node_open = ImGui::TreeNodeEx(to_string(scene->GetID()).c_str(), node_flags);
          if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_NODE")) {
                Node* payload_node = *(Node**)payload->Data;
                // handle the drop operation
                PLOGI<<"this is the payload Node"<<payload_node;
                PLOGI<<"payload ID"<<payload_node->GetID();
                PLOGI<<"RECIPIENT IS"<<scene->GetID();
                if(payload_node->m_parent!=scene)
                {
                    scene->attachChild(payload_node);
                    dragsource2 = 0;
                }
                ImGui::EndDragDropTarget();
        }
          }
    
    if (ImGui::IsItemClicked()) {
        selected = scene;
    }

    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
        Node *dragsource = scene;
        dragsource2 = scene;
        PLOGI<<"this is the Source NODE "<<dragsource;

        ImGui::SetDragDropPayload("SCENE_NODE", &dragsource, sizeof(Node*));
        ImGui::Text("Drag %s", to_string(scene->GetID()).c_str());
        ImGui::EndDragDropSource();
    } else if (dragsource2==scene)
    {
            dragsource2 = 0;
    }
    if (node_open) {
    

        for (int j =0; j<scene->m_children.size(); ++j) {
            if(scene->m_children[j]!=0)
                DrawTree(scene->m_children[j]);
        }
        ImGui::TreePop();
         
    }
    
    
}

void EditorUI::ImportedScenesWindowLeft(bool* p_open)
{
            ImGui::BeginChild("left pane", ImVec2(ImGui::GetWindowSize().x/2, 0), true); // Leave room for 1 line below us

            DrawTree(m_AM->scene);
         
            
            ImGui::EndChild();


}

void EditorUI::ImportedScenesWindowRight(bool* p_open)
{

            ImGui::BeginGroup();//this child window will scroll on it's own
            ImGui::BeginChild("item view1", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            
            if(selected) ImGui::Text("MyObject: %s", selected->GetName().c_str());
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {
               //do this kind of thing
               //if(selected->GetType().isDerived(ParentNode::TYPE)) DISPLAY Section related to that parent
                if (ImGui::BeginTabItem("Scene Details"))
                {
                    if(selected){
                    char text[128];
                    //string text = string("object id") + string("%i", m_AM->getModels()[selected]->GetID()); 
                    sprintf(text,"object ID : %i",  selected->GetID());
                    
                    ImGui::Text("%s",text);
                    ImGui::Text("Node type %s", selected->GetType().GetName().c_str());
                    if(selected->TYPE.IsDerived(Node::TYPE)) NodeProperties();


                    }
                    ImGui::EndTabItem();

                }
                if (ImGui::BeginTabItem("Description"))
                {
                    if(selected){
                    ImGui::TextWrapped("Scene Node");
                    }
                    ImGui::EndTabItem();

                }
               
                ImGui::EndTabBar();
            }
            
            ImGui::EndChild();
            
            ImGui::EndGroup();

}

void EditorUI::ImportedScenesWindow(bool* p_open)
{

    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("AssetManager Imported scenes Vector", p_open, ImGuiWindowFlags_MenuBar))
    {
        createNode();
        // Left
        ImportedScenesWindowLeft(p_open);
        ImGui::SameLine();
        // Right
        ImportedScenesWindowRight(p_open);
    }
    ImGui::End();
}

void EditorUI::NodeProperties(){
            static float translation[3];
            static float rotation[3];
            static float scale[3];
            static float angle;

                    translation[0] = selected->getTranslation().x;  
                    translation[1] = selected->getTranslation().y;  
                    translation[2] = selected->getTranslation().z;  

                    rotation[0] = selected->getRotationAxis().x;  
                    rotation[1] = selected->getRotationAxis().y;  
                    rotation[2] = selected->getRotationAxis().z;  

                    scale[0] = selected->getScale().x;  
                    scale[1] = selected->getScale().y;  
                    scale[2] = selected->getScale().z;  

                    angle = selected->getRotationAngle();
                    if(ImGui::InputFloat3("translation",translation))
                    {
                     selected->setTranslation(translation);  
                    }

                    if(ImGui::InputFloat("rotation angle",&angle))
                    {
                     selected->setRotationAngle(angle);  
                    }

                    if(ImGui::InputFloat3("rotation axis",rotation))
                    {
                     selected->setRotationAxis(rotation);  
                    }

                    if(ImGui::InputFloat3("Scale",scale))
                    {
                     selected->setScale(scale);  
                    }
                    ImGui::Text("Node's transform");
                    for(int i = 0; i<=3; ++i)
                    {
                        for(int j = 0; j <=3; ++j)
                        {
                            ImGui::Text("%f", selected->getWorldTransform()[i][j]);
                            ImGui::SameLine();
                        }
                        ImGui::NewLine();

                    }
                    glm::vec4 worldx, worldy, worldz, world;
                    glm::mat4 parentInverse = glm::mat4(1.0f);
                    if(selected->m_parent!=0)
                        parentInverse = glm::inverse(selected->m_parent->m_world);
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

                            const bool is_selected = (selected->getShader() == shaders[n]);
                            if (ImGui::Selectable(shaders[n]->GetName().c_str(), is_selected))
                                selected->setShader(shaders[n]);

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndListBox();
                    }
                    //end of shaders

}
void ObjectProperties(){}
void EditorUI::WorldNodeProperties(){

}
void EditorUI::AnimatedNodeProperties(){

}