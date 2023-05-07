#ifndef NODE_HPP
#define NODE_HPP
//for now put everything in node. every node is a 3d node.
#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include"Shader.hpp"
//we need to create new recursive methods for model
//there is the bones, the weight of influence of each bone on each vertex.
//then there is animations, which contain the key frames for translation rotation and scale.
#include"Mesh.hpp"
#include<Object.hpp>

#include "Camera.hpp"

#include <RTTI.hpp>
using namespace std;
enum nodeType
{
MESH
};
class Node : public Object
{

DECLARE_RTTI

public:
    /* data */
Node* m_parent;

vector<Node*> m_children;

//this one for TRS
glm::mat4 m_local;

//the model's transform  to world  coordinates
glm::mat4 m_world;//this one we pass to the shader
float m_angle;

//al relative to the parent node/ in world space
//we will create a matrix that completes these transforms
glm::vec3 m_rotation, m_translation, m_scale;


glm::mat4 m_localRotationMat, m_localTranslationMat, m_localScaleMat;

protected:
nodeType type; 
//create a new version of the processMesh function, one that returns pointers instead.
public:
    Node(/* args */);
    ~Node();
    int GetQuantity () const;//done
    void setParent(Node* parent);//done
    Node* getParent();//done
    int attachChild(Node* child);//done
    int detachChild(Node* child);//done
    Node* detachChildAt(int i);//done
    Node* getChild(int i);
    Node* setChild(int i, Node* child);
    void updateTransforms();
    virtual void Draw(Camera* camera, float deltaTime);
    void setTranslation(float vec[3]);
    void setRotationAxis(float vec[3]);
    void setScale(float vec[3]);
    void setRotationAngle(float angle);
    
 
    //glm::mat4 getLocalModelMatrix();

    
    glm::vec3 getTranslation();
    glm::vec3 getRotationAxis();
    glm::vec3 getScale();
    float getRotationAngle();
    glm::mat4& getWorldTransform();
    glm::mat4& getRelatifTransform();
    glm::mat4& getGuizmoTransform();
    void handleDetachements();
    virtual void save(Stream& stream);

//vector<Mesh*> m_meshData;

//static Node* selected;
static glm::mat4 view;
static glm::mat4 projection;


};

#endif
