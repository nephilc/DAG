#include "Node.hpp"
#include <plog/Log.h> 

//the world tranform is going to be passed to gpu, it should contain the transform in model space aswell.




Node* Node::selected = 0;
glm::mat4 Node::view = glm::mat4(1.0f);
glm::mat4 Node::projection = glm::mat4(1.0f);
bool Node::manipulated = false;
bool Node::rotation_gizmo = false;
glm::mat4 Node::gizmo = glm::mat4(1.0f);
glm::mat4 Node::delta = glm::mat4(1.0f);

//if no parent the model will be equal to the world
Node::Node(/* args */)
{
    PLOGE<< "calling node constructor." ;
    m_parent = 0;//not initializing this pointer var, give a bug in the root node's tranform.
    //m_world = glm::mat4(1.0f);
    m_relToParent = glm::mat4(1.0f);
    m_guizmo = glm::mat4(1.0f);
    m_world = m_local = m_editorlocal= m_editorWorld = m_WorldTranslation = m_LocalTranslation =m_localRotationMat= m_localTranslationMat=m_localScaleMat = glm::mat4(1.0f);
    this->SetName(to_string(this->GetID()));
    m_translation = glm::vec3(0.0f);
    m_rotation = glm::vec3(1.0f);
    m_scale = glm::vec3(1.0f);
    m_angle = 0.0f;

    //we need to initialize it here, first, when using the editor.
    m_relToParent = glm::translate(m_relToParent, m_translation); // translate it down so it's at the center of the scene
    m_relToParent = glm::scale(m_relToParent, m_scale);	// it's a bit too big for our scene, so scale it down
    m_relToParent = glm::rotate(m_relToParent,m_angle, m_rotation);

}

Node::~Node()
{
    PLOGE<<"CALLING NODE DESTRUCTOR";
    for (int i = 0; i < (int)m_children.size(); i++)
    {
        Node* child = detachChildAt(i);
        //delete child = 0;
    }

}

void Node::updateTransforms()
{
    //PLOGE<<"updating tranforms";
    if(this->m_parent != 0)
    {
        //m_relToParent = glm::mat4(1.0f);
        //m_relToParent = glm::translate(m_relToParent, m_translation); // translate it down so it's at the center of the scene
        //m_relToParent = glm::scale(m_relToParent, m_scale);	// it's a bit too big for our scene, so scale it down
        //m_relToParent = glm::rotate(m_relToParent,m_angle, m_rotation);
   
//        m_world = m_parent->m_world /** m_guizmo **/ * m_relToParent;
        //m_local= m_parent->m_local * m_local;
        //trs
        //since im storign orientation in a matrix, we should be avoiding gimball lock
        m_local = m_localTranslationMat*m_localRotationMat*m_localScaleMat;
        m_WorldTranslation = m_parent->m_WorldTranslation *  m_LocalTranslation;
        m_world =  m_parent->m_world * m_local;
        //m_world = m_local;
    }
    else
    {
        /*
        m_relToParent = glm::mat4(1.0f);
        m_relToParent = glm::translate(m_relToParent, m_translation); // translate it down so it's at the center of the scene
        m_relToParent = glm::scale(m_relToParent, m_scale);	// it's a bit too big for our scene, so scale it down
        m_relToParent = glm::rotate(m_relToParent,m_angle, m_rotation);
   
        m_world = m_relToParent;
        */
       m_world = m_local;
    }

}
void Node::Draw(Camera* camera, float deltaTime)
{
    //set the world matrix then draw
    //PLOGD<<"drawing scene";
    //if the scene is static, one only
    updateTransforms();

    for(int i = 0; i <m_children.size(); ++i)
    {
        m_children[i]->Draw(camera, deltaTime);
    }

}

glm::mat4 Node::getLocalModelMatrix()
{
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
                         glm::radians(m_euler.x),
                         glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
                         glm::radians(m_euler.y),
                         glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
                         glm::radians(m_euler.z),
                         glm::vec3(0.0f, 0.0f, 1.0f));

    // Y * X * Z
    const glm::mat4 roationMatrix = transformY * transformX * transformZ;

    // translation * rotation * scale (also know as TRS matrix)
    return glm::translate(glm::mat4(1.0f), m_translation) *
                roationMatrix *
                glm::scale(glm::mat4(1.0f), m_scale);
}

void Node::setParent (Node* parent)
{
    if(parent!=0){
    PLOGD<<"SET PARENT METHOD";
    //PLOGD<<"The parent would be "<<parent;

    if(m_parent!=0)
    //m_parent->detachChild(this);
    PLOGD<<"The parent would be "<<parent;

    if(parent!=0){
    
    m_parent = parent;
    }
    }
}
Node* Node::getParent ()
{
    return m_parent;
}
int Node::attachChild (Node* child)
{   
    //well, first, one needs to remove the child from it's parent's children aswell.
    PLOGD<<"ABOUT  TO CALL SET PARENT ON CHILD " << child << " whose ID IS " << child->GetID();


    child->setParent(this);

    // attach child in first available slot (if any)
    int iQuantity = (int)m_children.size();
    for (int i = 0; i < iQuantity; i++)
    {
        if (m_children[i] == 0)
        {
            m_children[i] = child;
            return i;
        }
    }

    // all slots used, increase array size
    m_children.push_back(child);
    return iQuantity;
}

void Node::handleDetachements()
{
                        for (int i = 0; i <m_children.size(); ++i)
                        //for (vector::iterator it = m_children.begin(); it != m_childre.end(); it++)
                        {
                            
                        if(m_children[i]!=0){
                        PLOGI<<"GOING THORUGH CHILD "<<m_children[i]->GetID();
                        //m_children[i]->handleDetachements();
                        if(m_children[i]->m_parent!=this)
                        {   
                            
                            m_children.erase(m_children.begin()+i);
                            //int j = detachChild(m_children[i]);
                            PLOGI<<"AFTER DETACH CHILD "<< i;
                            PLOGI<<"CHILDREN SIZE IS "<< m_children.size();
                            return;
                        }
                        m_children[i]->handleDetachements();
                        
                        }
                        }
                        

                    }



int Node::GetQuantity () const
{
    return (int)m_children.size();
}

int Node::detachChild (Node* child)
{
    PLOGD<<"ABOUT TO CALL DETACH CHILD";
    if (child)
    {
        // search to see if child exists
        for (int i = 0; i < (int)m_children.size(); i++)
        {
            if (m_children[i] == child)
            {
                    PLOGD<<"FOUND CHILD " << i;

                // child found, detach it
                //child->setParent(0);
                m_children[i] = (Node*)0;
                    PLOGD<<"just set it to 0";

                return i;
            }
        }
    }

    return -1;
}
Node* Node::detachChildAt (int i)
{
    if (0 <= i && i < (int)m_children.size())
    {
        Node* child = m_children[i];
        if (child)
        {
            // child exists in slot, detach it
            child->setParent(0);
            m_children[i] = 0;
        }
        return child;
    }
    return 0;
}

Node* Node::setChild (int i, Node* child)
{

    if (0 <= i && i < (int)m_children.size())
    {
        // detach child currently in slot
        Node* spkPreviousChild = m_children[i];
        if (spkPreviousChild)
        {
            spkPreviousChild->setParent(0);
        }

        // attach new child to slot
        if (child)
        {
            child->setParent(this);
        }

        m_children[i] = child;
        return spkPreviousChild;
    }

    // index out of range, increase array size and attach new child
    child->setParent(this);
    m_children.push_back(child);
    return 0;
}

Node* Node::getChild (int i)
{
    if (0 <= i && i < (int)m_children.size())
    {
        return m_children[i];
    }
    return 0;
}

void Node::setTranslation(float vec[3])
{
    m_translation.x = vec[0];
    m_translation.y = vec[1];
    m_translation.z = vec[2];
}
void Node::setRotationAxis(float vec[3])
{
    m_rotation.x = vec[0];
    m_rotation.y = vec[1];
    m_rotation.z = vec[2];

}
void Node::setScale(float vec[3])
{
    m_scale.x = vec[0];
    m_scale.y = vec[1];
    m_scale.z = vec[2];

}

void Node::setRotationAngle(float angle)
{

    m_angle = angle;
}   

glm::vec3 Node::getTranslation()
{
    return m_translation;
}

glm::vec3 Node::getRotationAxis()
{
    return m_rotation;
}

glm::vec3 Node::getScale()
{
    return m_scale;
}


float Node::getRotationAngle()
{
    return m_angle;
}

glm::mat4& Node::getWorldTransform()
{
    return m_world;
}
void Node::setShader(Shader* shader)
{
    m_shader = shader;
}    

Shader* Node::getShader()
{
    return m_shader;
}    


glm::mat4& Node::getRelatifTransform()
{
    return m_relToParent;
}



glm::mat4& Node::getGuizmoTransform()
{
    return m_guizmo;
}

/*
void Node::DrawTree(){
    ImGui::TreeNodeEx(to_string(GetID()).c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick);
    if (ImGui::IsItemClicked()) {
        // handle user click on this node
    }
    for (Node* child : m_children) {
        child->DrawTree();
    }
    ImGui::TreePop();
}
*/
/*
void Node::DrawTree(){
    if (ImGui::Button("+")) {
        // handle user click on this node
    }
    ImGui::SameLine();
    
    ImGui::Text("Node whose ID is %s", to_string(GetID()).c_str());
    
    if (ImGui::IsItemClicked()) {
        // handle user click on this node
    }
    for (Node* child : m_children) {
        ImGui::Indent();
        child->DrawTree();
        ImGui::Unindent();
    
    }
    //ImGui::TreePop();
}
*/

void Node::DrawTree() {
    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    if (selected==this) {
        node_flags |= ImGuiTreeNodeFlags_Selected;
    }
    bool node_open = ImGui::TreeNodeEx(to_string(GetID()).c_str(), node_flags);
          if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_NODE")) {
                Node* payload_node = *(Node**)payload->Data;
                // handle the drop operation
                PLOGI<<"this is the payload Node"<<payload_node;
                PLOGI<<"payload ID"<<payload_node->GetID();
                PLOGI<<"RECIPIENT IS"<<GetID();
                if(payload_node->m_parent!=this)
                    attachChild(payload_node);
            
                ImGui::EndDragDropTarget();
        }
          }
    
    if (ImGui::IsItemClicked()) {
        selected = this;
    }
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
        Node *dragsource = this;
        PLOGI<<"this is the Source NODE "<<dragsource;

        ImGui::SetDragDropPayload("SCENE_NODE", &dragsource, sizeof(Node*));
        ImGui::Text("Drag %s", to_string(GetID()).c_str());
        ImGui::EndDragDropSource();
    }
    if (node_open) {
    

        for (int j =0; j<m_children.size(); ++j) {
            if(m_children[j]!=0)
                m_children[j]->DrawTree();
        }
        ImGui::TreePop();
         
    }
    
    
}