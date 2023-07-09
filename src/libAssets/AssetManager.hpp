#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP
#include<map>
#include<unordered_map>
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
#include <ScreenCanvas.hpp>
#include<Action.hpp>
#include<WorldNode.hpp>
#include<KeyMap.hpp>

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
    static AssetManager* am;
        AssetManager(/* args */);

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
    map<string, ScreenCanvas*> screenCanavases;

    vector<Model*> v_models;
    vector<Node*> v_scenes;
    vector<Shader*> v_shaders;
    vector<Animation*> v_Animations;
    vector<FrameBuffer*> v_frameBuffers;
    vector<ScreenCanvas*> v_ScreenCanvases;

    static FrameBuffer* mainBuffer;
    FrameBuffer *currentFrameBuffer;

    Node* currentScene;

    // "File://" subsitute
    std::string fileRoot;



public:
    static std::string configFile;
    std::string basePath;//FILE:// this base path will have multiple uses
    //in the editor
    //will be used to split absolute paths of the models, when saving them. so that all paths saved will be relative to the executable.
    //in the game, or deliverable, we know all paths are relative to the executable, we will still use it to load, and save if needed.
    //on android we can put the  absolute path to the application asset folder, here. and use it to extract assets, load and save.
    //this is the one i will use################################################
    //map : char====> Action string;
    //Thes would be default action maps
//    std::unordered_map<string, Action*> KeyboardActionMap;
//    std::unordered_map<string, Action*> MouseActionMap;
 //   std::unordered_map<string, Action*> GamePadActionMap;
    std::vector<string> keyBoardVector;
    std::vector<string> MouseVector;
    std::vector<string> GamePadVector;





    //##################DIFFERENT OBJECTS WILL REQUIRE DIFFERENT MAPS#####################################################
    //##################THESE POINTERS WILL BE SET DEPENDING ON THE CURRENT APPLICATION OBJECT IN CONTROL#################
    //std::unordered_map<string, Action*> *currentKeyboardActionMap;
    //std::unordered_map<string, Action*> *currentMouseActionMap;
    //std::unordered_map<string, Action*> *currentGamePadActionMap;

    //###############
    KeyMap* currentMouseKeyMap;
    KeyMap* currentKeyboardKeyMap;
    KeyMap* currentGamepadKeyMap;
    
    std::vector<KeyMap*> KeyMapsVector;



    /// <summary>
    /// action vectors, the ones frpom which we will pick actions
    /// </summary>
    std::vector<Action*> KeyActionsVector;//any key, controller and gamepad keys, have the same method signature
    std::vector<Action*> MouseActionsVector;//Mouse




    ~AssetManager();
    void loadModel(string path);
    void loadScene(string path);
    void loadShader(string vpath, string fpath, string name);
    void loadAnimation(string vpath, Model* model);

    //the path should include the fileName
    void saveScene(string filePath);

    static AssetManager* getInstance();


    void addScene(Node* scene);
    void registerAction(Action* action);
    void setDefaultActionMaps();

    void setCurrentKeyMap(KeyMap* keyMap);
    KeyMap* getCurrentKeyMap();



    Model* getModel(const string name);
    ScreenCanvas* getScreenCanvas(const string name);

    const vector<Model*>& getModels() const;
    const vector<Node*>& getScenes() const;
    const vector<Shader*>& getShaders() const;
    const vector<Animation*>& getAnimations() const;
    const vector<FrameBuffer*>& getFrameBuffers() const;
    const vector<ScreenCanvas*>& getScreenCanvases() const;

    FrameBuffer* getCurrentFrameBuffer();
    void makeBufferCurrent(FrameBuffer *buffer);

    void CreateDefaults();


    
    
    void setCurrentScene(Node* scene);
    Node* getCurrentScene();


    void createScreenCanvas(int width, int height, string name);

    void createFrameBuffer(int width, int height, string name);
    FrameBuffer* getFrameBuffer(string name);
    //these will have to be static for they have to be accessed from non static members of other classes
    static FrameBuffer* getMainBuffer();    
    static void  recreateMainFB(int width, int height);
    void createmainFB(int width, int height);
    void createKeyMap();

    void getDefault(const Rtti &type, Node* parent);
    

    //#################################################
    //################ D E F A U L T S ################
    //#################################################
    Model* defaultModel;
    Animation* defaultAnimation;
    Animator* defaultAnimator;
    AnimatedNode* defaultaniNode;
    Shader* defaultShader;
    Shader* defaultAniShader;


};


#endif