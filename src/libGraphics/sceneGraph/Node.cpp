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
    m_world = glm::mat4(1.0f);
    m_relToParent = glm::mat4(1.0f);
    m_guizmo = glm::mat4(1.0f);
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
    
    if(selected == this & this->m_parent != 0 )
    {
        float matrixTranslation[3], matrixRotation[3], matrixScale[3];
        
        ImGuizmo::DecomposeMatrixToComponents(&delta[0][0], matrixTranslation, matrixRotation, matrixScale);
        
        m_translation.x += matrixTranslation[0];
        m_translation.y += matrixTranslation[1];
        m_translation.z += matrixTranslation[2];
        
        m_euler.x += glm::radians(matrixRotation[0]);        
        m_euler.y += glm::radians(matrixRotation[1]);        
        m_euler.z += glm::radians(matrixRotation[2]);        
//        m_angle += glm::radians(matrixRotation[1]);        
        if(manipulated) PLOGD<<matrixRotation[0]<<" "<<matrixRotation[1]<<" "<<matrixRotation[2];
        
        
        
        //m_world = old_world;
    
    }
    else if (selected == this & this->m_parent == 0 )
    {

        glm::mat4 old_world = m_relToParent;
        glm::mat4 inv = glm::inverse(old_world);
        //for the root node the vectors are in world coordinates
        glm::mat4 coeff = m_world * inv;
        //m_translation.x += coeff[3][0];
        //m_translation.y += coeff[3][1];
        //m_translation.z += coeff[3][2];
        
    }
    
    //glm::decompose
    //recompose the matrix, this is what is generally, when not using the editor
    //but in order to change the position of a node, one must change it's position relatif to its parent
    if(this->m_parent != 0)
    {
        
        m_local = getLocalModelMatrix();
   
        m_world = m_parent->m_world * m_local;

    }
    else
    {
        m_relToParent = glm::mat4(1.0f);
        m_relToParent = glm::translate(m_relToParent, m_translation); // translate it down so it's at the center of the scene
        m_relToParent = glm::scale(m_relToParent, m_scale);	// it's a bit too big for our scene, so scale it down
        m_relToParent = glm::rotate(m_relToParent,m_angle, m_rotation);
   
        m_world = m_relToParent;
        
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

void Node::DrawTree()
{        
    static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    static int selection_mask = (1 << 2);
            static int node_clicked = -1;//we use this variable to update selection mask after the loop.
                // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
                // To alter selection we use IsItemClicked() && !IsItemToggledOpen(), so clicking on an arrow doesn't alter selection.
                ImGuiTreeNodeFlags node_flags = base_flags;
                bool dragSource = false;
                const bool is_selected = (selection_mask & (1 << this->GetID())) != 0;
                static int frame_delay = 2;//dont process the drop until the frame delay, becomes 0
                static int drag_source = -1;

                if (is_selected)
                {
                    node_flags |= ImGuiTreeNodeFlags_Selected;
                    selected = this;
                    gizmo = this->m_world;
                }   
                    if(drag_source == this->GetID()) 
                    {
                        ImGui::SetNextItemOpen(false);
                        std::cout<<this->GetID()<<" is drag SOURCE ID"<<std::endl;

                    
                    }
                    bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)this->GetID(), node_flags, "Selectable Node %d", this->GetID());
                    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                        node_clicked = this->GetID();
                        //here we can set a pointer to the object represented by this node.
                    if (ImGui::BeginDragDropSource())
                    {
                        dragSource = true;
                        drag_source = this->GetID();//this id solution works, maybe the only solution i need to use.
                        ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                        ImGui::Text("This is a drag and drop source");
                        ImGui::EndDragDropSource();
                    }
                    else if(drag_source == this->GetID())//let the node that changed the state, change it back
                    {
                        dragSource = false;
                        drag_source = -1;
   
                    }

                    if (ImGui::BeginDragDropTarget())
                    {
                        std::cout<<this->GetName()<<" is drag drop target"<<std::endl;
                        //Node* dropped = (Node*)ImGui::GetDragDropPayload()->Data;
                        //std::cout<<dropped->GetName()<<" is dropped payload"<<std::endl;

                    }

                    if(dragSource & node_open)
                    {
                         //std::cout<<this->GetName()<<" is drag drag source"<<std::endl;
                         node_open =false;

                        ImGui::TreePop();

                    }
                    if (node_open & !dragSource)
                    {
                        for (int i = 0; i <m_children.size(); ++i)
                        {
            

                        m_children[i]->DrawTree();
                        }
                        ImGui::TreePop();
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

void Node::setParent (Node* parent)
{
    m_parent = parent;
}
Node* Node::getParent ()
{
    return m_parent;
}
int Node::attachChild (Node* child)
{   
    //well, first, one needs to remove the child from it's parent's children aswell.

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


int Node::GetQuantity () const
{
    return (int)m_children.size();
}

int Node::detachChild (Node* child)
{
    if (child)
    {
        // search to see if child exists
        for (int i = 0; i < (int)m_children.size(); i++)
        {
            if (m_children[i] == child)
            {
                // child found, detach it
                child->setParent(0);
                m_children[i] = 0;
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
