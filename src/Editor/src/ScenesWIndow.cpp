#include<EditorUI.hpp>
#include <gtc/type_ptr.hpp>
#include<WorldNode.hpp>
#include<NodeFactory.hpp>









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
            static Rtti *selectedType = nullptr;
            ImGui::Text("%d", Node::TYPE.nodeList.size());
            for(Rtti* type : Rtti::nodeList){
            if (ImGui::Selectable(type->GetName().c_str(), selectedType == type, ImGuiSelectableFlags_DontClosePopups))
                    selectedType = type;
            }
            
            ImGui::Separator();
            if(ImGui::Button("add", ImVec2(120, 0)) && selectedType!=nullptr) {
                //add node here depedning on the type of the selected node
                if(Node * createdNode = NodeFactory::create(selectedType))
                    selected->attachChild(createdNode);
                ImGui::CloseCurrentPopup();
                
            }
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
    bool node_open = ImGui::TreeNodeEx(scene->GetName().c_str(), node_flags);
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
        //PLOGI<<"this is the Source NODE "<<dragsource;

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

            DrawTree(m_AM->getCurrentScene());
         
            
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
               //if(selected->GetType().isDerived(::TYPE)) DISPLAY Section related to that parent
                if (ImGui::BeginTabItem("Scene Details"))
                {
                    if(selected){
                    ImGui::Text("Node type %s", selected->GetType().GetName().c_str());
                    ObjectProperties(selected);
                    if(selected->GetType().IsExactly(WorldNode::TYPE)){
                        WorldNodeProperties();
                    }
                    else{
                        NodeProperties();
                        if(selected->GetType().IsDerived(GeometryNode::TYPE)){
                        GeometryNodeProperties();
                        }
                        if (selected->GetType().IsDerived(ModelNode::TYPE)) {
                            ModelNodeProperties();
                        }
                        if (selected->GetType().IsDerived(AnimatedNode::TYPE)) {
                            AnimatedNodeProperties();
                        }
                    }
                    
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
        playButton();
        saveSceneButton();
        sceneCombo();
        newSceneButton();
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
                    
                        if (ImGui::CollapsingHeader("Node Properties", ImGuiTreeNodeFlags_None))
        {

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

                    
                    }

}
void EditorUI::ObjectProperties(Object* object){
        if (ImGui::CollapsingHeader("Object Properties", ImGuiTreeNodeFlags_None))
        {
                    char text[128];
                    //string text = string("object id") + string("%i", m_AM->getModels()[selected]->GetID()); 
                    sprintf(text,"object ID : %i",  object->GetID());
                    
                    ImGui::Text("%s",text);

            static char str0[128] = "Object Name";
            sprintf(str0,"%s",  object->GetName().c_str());

            if(ImGui::InputText("Object Name", str0, IM_ARRAYSIZE(str0)))
                object->SetName(string(str0));
        }
}
void EditorUI::WorldNodeProperties(){
        WorldNode *localPointer = dynamic_cast<WorldNode*>(selected);
        static float afCLearColor[4];

    if (ImGui::CollapsingHeader("WorldNode Properties", ImGuiTreeNodeFlags_None))
        {
    if(ImGui::InputFloat4("Clear Color",afCLearColor))
    {
                     if(localPointer!=nullptr)
                     {
                        localPointer->setClearColor(afCLearColor[0],afCLearColor[1],afCLearColor[2],afCLearColor[3]);
                     }  
                     else{
                        PLOGE<<"DYNAMIC CAST FAILED  TO TYPE" <<WorldNode::TYPE.GetName();
                     }
    }

        }
        
    


}

void EditorUI::AnimatedNodeProperties(){
    if(ImGui::CollapsingHeader("Animated Node Properties")){
    AnimatedNode* localPointer = dynamic_cast<AnimatedNode*>(selected);
    static char* buttonText = "";
    //will need to modify the animator aswell.
    if(localPointer->getPlayState())buttonText="Stop";
    else buttonText="play";
    if(ImGui::Button(buttonText))
    {
        if(localPointer->getPlayState()) localPointer->stop();
        else localPointer->play();
    }
    ImGui::SameLine();
    if (ImGui::Button("set null"))
    {
        localPointer->setAnimation(nullptr);
        Animator *animator = localPointer->getAnimator();
        if(animator!=nullptr)animator->PlayAnimation(nullptr);

    }
    loadAnimationButton(localPointer);
    vector<Animation*> animations = m_AM->getAnimations();
    if (ImGui::BeginListBox("Animations"))
    {
        for (int n = 0; n < animations.size(); n++)
        {
            //item_current_idx = n;

            const bool is_selected = (localPointer->getAnimation() == animations[n]);
            if (ImGui::Selectable(animations[n]->GetName().c_str(), is_selected)) {
                localPointer->setAnimation(animations[n]);
                Animator *animator = localPointer->getAnimator();
                if(animator!=nullptr) animator->PlayAnimation(animations[n]);

            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }
    AnimatedNodePickModel();
    }
    

}
void EditorUI::GeometryNodeProperties(){
    GeometryNode *localPointer = dynamic_cast<GeometryNode*>(selected);
    if (ImGui::CollapsingHeader("GeometryNode Properties", ImGuiTreeNodeFlags_None))
    {               if(ImGui::Button("set null") & selected!=0)   localPointer->setShader(nullptr);

        //shaders 
                    static int item_current_idx = 0; // Here we store our selection data as an index.
                    vector<Shader*> shaders = m_AM->getShaders();
                    if (ImGui::BeginListBox("listbox 1"))
                    {
                    for (int n = 0; n < shaders.size(); n++)
                        {
                            //item_current_idx = n;

                            const bool is_selected = (localPointer->getShader() == shaders[n]);
                            if (ImGui::Selectable(shaders[n]->GetName().c_str(), is_selected))
                                localPointer->setShader(shaders[n]);

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndListBox();
                    }
                    //end of shaders

                    static int item_current_idx1 = 0; // Here we store our selection data as an index.
                    if (ImGui::BeginListBox("DRAW MODE"))
                    {
                        for (int MD = MD_FIRST+1; MD < MD_LAST; MD++)
                        {
                            DrawMode MDType = static_cast<DrawMode>(MD);

                            const bool is_selected1 = (localPointer->drawMode == MDType);
                            if (ImGui::Selectable(DrawModeStrings[MD-1], is_selected1))
                                localPointer->drawMode = MDType;

                            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                            if (is_selected1)
                                ImGui::SetItemDefaultFocus();
                        }
                        ImGui::EndListBox();
                    }
                    //end of shaders

    }

}
void EditorUI::AnimatedNodePickModel()
{
    AnimatedNode *localPointer = dynamic_cast<AnimatedNode*>(selected);
               if(ImGui::Button("set null A N") & selected != 0)   localPointer->m_model = nullptr;

        //shaders 
                    static int item_current_idx1 = 0; // Here we store our selection data as an index.
                    vector<Model*> models = m_AM->getModels();
                    if (ImGui::BeginListBox("Animated models"))
                    {
                    for (int n = 0; n < models.size(); n++)
                        {
                            //item_current_idx = n;

                            const bool is_selected = (localPointer->getModel() == models[n]);

                            if (ImGui::Selectable(models[n]->GetName().c_str(), is_selected))
                                localPointer->m_model = models[n];

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndListBox();
                    }
                    //end of shaders



}
void EditorUI::ModelNodeProperties(){
    ModelNode *localPointer = dynamic_cast<ModelNode*>(selected);
    if (ImGui::CollapsingHeader("ModelNode Properties", ImGuiTreeNodeFlags_None))
    {               if(ImGui::Button("set null2") & selected != 0)   localPointer->setModel(nullptr);

        //shaders 
                    static int item_current_idx1 = 0; // Here we store our selection data as an index.
                    vector<Model*> models = m_AM->getModels();
                    if (ImGui::BeginListBox("listbox models"))
                    {
                    for (int n = 0; n < models.size(); n++)
                        {
                            //item_current_idx = n;

                            const bool is_selected = (localPointer->getModel() == models[n]);

                            if (ImGui::Selectable(models[n]->GetName().c_str(), is_selected))
                                localPointer->setModel(models[n]);

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                    ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndListBox();
                    }
                    //end of shaders

    }

}


void EditorUI::playButton() {
    ImGui::SameLine();
    // Create the button
    if (ImGui::Button("play", ImVec2(40, 20)))
    {
        app->imode = SIMULATION;
        updateInputFlags(SIMULATION);
        app->disableCursor();
        // Handle button press here
    }
}

void EditorUI::newSceneButton() {
    ImGui::SameLine();
    // Create the button
    if (ImGui::Button("new Scene"))
    {
        Node* newScene = new WorldNode(1.0, 1.0, 1.0, 1.0);
        m_AM->addScene(newScene);
        m_AM->setCurrentScene(newScene);    

    }
}

void EditorUI::saveSceneButton() {
    bool save = false;
    ImGui::SameLine();
    // Create the button
    if (ImGui::Button("Save scene"))
    {
        save = true;
        //open pop up model to get the location where to save the file
        // open stream to file
        // save the asset managers current scene, pass the stream to it.
        //save scene
    }
    if (save)
        ImGui::OpenPopup("Save scene");


    if (file_dialog.showFileDialog("Save scene", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), "*.xdg"))
    {
        std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
        std::cout << file_dialog.ext << std::endl;              // Access ext separately (For SAVE mode)
        //Do writing of files based on extension here
        //stream.myfile.close();

        m_AM->saveScene(file_dialog.selected_path + ".xdg");

    }
}


void EditorUI::loadKeyMapButton() {
    bool save = false;
    ImGui::SameLine();
    // Create the button
    if (ImGui::Button("load key map"))
    {
        save = true;
        //open pop up model to get the location where to save the file
        // open stream to file
        // save the asset managers current scene, pass the stream to it.
        //save scene
    }
    if (save)
        ImGui::OpenPopup("Load Key Map");


    if (file_dialog.showFileDialog("Load Key Map", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".kmf"))
    {
        std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
        std::cout << file_dialog.ext << std::endl;              // Access ext separately (For SAVE mode)
        //Do writing of files based on extension here
        //stream.myfile.close();

        m_AM->loadKeyMap(file_dialog.selected_path);

    }
}


void EditorUI::saveKeyMapButton(KeyMap* km) {
    bool save = false;
    ImGui::SameLine();
    // Create the button
    if (ImGui::Button("save key map"))
    {
        save = true;
        //open pop up model to get the location where to save the file
        // open stream to file
        // save the asset managers current scene, pass the stream to it.
        //save scene
    }
    if (save)
        ImGui::OpenPopup("save Key Map");


    if (file_dialog.showFileDialog("save Key Map", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), ".kmf"))
    {
        std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
        std::cout << file_dialog.ext << std::endl;              // Access ext separately (For SAVE mode)
        //Do writing of files based on extension here
        //stream.myfile.close();

        m_AM->saveKeyMap(file_dialog.selected_path + ".kmf", km, file_dialog.selected_fn+".kmf");

    }
}


void EditorUI::loadAnimationButton(AnimatedNode* AniNode) {
    bool save = false;
    ImGui::SameLine();
    // Create the button
    if (ImGui::Button("load Animation"))
    {
        save = true;
        //open pop up model to get the location where to save the file
        // open stream to file
        // save the asset managers current scene, pass the stream to it.
        //save scene
    }
    if (save)
        ImGui::OpenPopup("load Animation");


    if (file_dialog.showFileDialog("load Animation", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), "*.*"))
    {
        std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
        std::cout << file_dialog.ext << std::endl;              // Access ext separately (For SAVE mode)
        //Do writing of files based on extension here
        //stream.myfile.close();
        PLOGD << file_dialog.selected_path;
        m_AM->loadAnimation(file_dialog.selected_path, AniNode->getModel());

    }
}

void EditorUI::sceneCombo() {
    ImGui::SameLine();
    static int item_current_idx = 0; // Here we store our selection data as an index.
    const char* combo_preview_value = "scene1";  // Pass in the preview value visible before opening the combo (it could be anything)
    if (ImGui::BeginCombo(string("select scene").c_str(), combo_preview_value, ImGuiComboFlags_NoPreview))
    {
        vector<Node*> scenes = m_AM->getScenes();
        for (int n = 0; n <scenes.size(); n++)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(scenes[n]->GetName().c_str(), is_selected)) {
                item_current_idx = n;
                m_AM->setCurrentScene(scenes[n]);
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

}
//animations dont work accross models by default