#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP
#include<map>
#include<string>
#include<Mesh.hpp>
#include<Model.hpp>
#include<Shader.hpp>
#include<vector>
#include <Node.hpp>
#include <FrameBuffer.hpp>
#include <RTTI.hpp>
#include <animation.h>
#include <animator.h>
#include <AnimatedNode.hpp>


//in the buffer you put the vertexdata.
//genbuffer+bind buffer+bufferdata

//specify the attributes of each vertex(position, texture coords, normal...)
//bind the vertex array and specify the position of each attribute in the vertex buffer.
//gen texture, bind texture, set paramtres, pass image data, generate mipmaps.


//on render binding the textures on corresponding texture units using the texture ids.

//use the program, set get the matrices from glm and the camera class, 
//bind vao of the object we want to draw, gldrawarrays.
//the mode to draw arrays is triangles, strating index in the enabled array. the number of vertices in the vao.

//there is draw array and draw elements

//suing draw elements for indexed drawing.

//all kinds of buffers(array biffer, transform feedback buffer..)
//telling opengl how to interpret the data in buffers. that is attribute arrays.
//enabling each attribute array using its pointer
//vao store multiple attribute pointers for each vbo.
//we could generate a bunch of buffers at once
//telling opengl how to manage buffer memory
//vao also stores glbindbuffer calls, so dont unbind buffers before the vao.
//setting the uniform sampler to the correct texture unit

typedef unsigned int UI;

using namespace std;
class AssetManager
{
private:
    /* data */
    //a  bunch of maps here
    map<string, UI> vertexBuffers;//Vertex buffer ids
    map<string, UI> attribute_objects;//the vao ids
    map<string, UI> textures;//texture ids
    map<string, UI> elementBuffers;//elements buffer for indexed drawing.
    //vector would be much more practical in certain cases
    map<string, Model*> models;
    map<string, Shader*> shaders;
    map<string, FrameBuffer*> frameBuffers;

    vector<Model*> v_models;
    vector<Node*> v_scenes;
    vector<Shader*> v_shaders;
    vector<FrameBuffer*> v_frameBuffers;

    static FrameBuffer* mainBuffer;

    

public:
    AssetManager(/* args */);
    ~AssetManager();
    void loadModel(string path, string name);
    void loadScene(string path, string name);
    void loadShader(string vpath, string fpath, string name);
    Model* getModel(const string name);
    const vector<Model*>& getModels() const;
    const vector<Node*>& getScenes() const;
    const vector<Shader*>& getShaders() const;
    const vector<FrameBuffer*>& getFrameBuffers() const;

    void CreateDefaults();


    void loadScene();
    Node* scene;

    void createFrameBuffer(int width, int height, string name);
    FrameBuffer* getFrameBuffer(string name);

    void  recreateMainFB(int width, int height);
    FrameBuffer* getMainBuffer();
    void createmainFB(int width, int height);

    void getDefault(const Rtti &type, Node* parent);
    //#################################################
    //################ D E F A U L T S ################
    //#################################################
    Model *defaultModel;
    Animation defaultAnimation;
    Animator* defaultAnimator;
    AnimatedNode* defaultaniNode;
    Shader* defaultShader;
    Shader* defaultAniShader;
    


};


#endif