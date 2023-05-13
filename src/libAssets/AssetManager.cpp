#include "AssetManager.hpp"
#include <plog/Log.h>


FrameBuffer* AssetManager::mainBuffer = 0;
Action *AssetManager::NoAction = new Action("No Action");

AssetManager::AssetManager(/* args */)
{
    PLOGI<<"CREATING ASSETMANAGER";
    mainBuffer = new FrameBuffer(1280, 720);//the resolution of the framebuffer will determine the quality of the image
    v_frameBuffers.push_back(mainBuffer);

    makeBufferCurrent(mainBuffer);
    //CreateDefaults();

}

void AssetManager::CreateDefaults()
{
    PLOGI<<"CREATING DEFAULTS";

    loadShader("shaderPrograms/animation.vs", "shaderPrograms/1.model_loading.fs", "ourShader1");
    loadShader("shaderPrograms/1.model_loading.vs", "shaderPrograms/1.model_loading.fs", "ourShader2");
    loadModel("3dmodels/arissa1/arissa1.dae", "arissa");

    defaultShader = getShaders()[1];
    defaultAniShader = getShaders()[0];

    defaultModel = getModel("arissa");
    defaultAnimation = Animation("3dmodels/Dying/Dying.dae", defaultModel);
    defaultAnimator = new Animator(&defaultAnimation);
    defaultaniNode = new AnimatedNode(defaultModel, defaultAniShader, defaultAnimator, defaultAnimation);

    //#################These would be dafault action maps
    currentMouseActionMap = &MouseActionMap;
    currentKeyboardActionMap = &KeyboardActionMap;
    currentGamePadActionMap = &GamePadActionMap;

}

AssetManager::~AssetManager()
{
    PLOGI<<"DESTROYING ASSETMANAGER";
}
ScreenCanvas* AssetManager::getScreenCanvas(const string name)
{
    return screenCanavases[name];
}


void AssetManager::loadModel(string path, string name)
{
    if(models.count(name) > 0)
    {
        //if name already exists append the object id to it.
        Model *model = new Model(path);
        std::ostringstream oss;
        oss << name <<model->GetID();
        string newName = oss.str();
        models[newName] = model;
        model->SetName(newName);
        v_models.push_back(model);

    }
    else{
    Model *model = new Model(path);
    models[name] = model;
    model->SetName(name);
    v_models.push_back(model);
    }
}


void AssetManager::loadScene(string filePath)
{

    //create stream
    //call load on world node
    // //the file will be read recursivly
    //load methods on object classes will be called
    //WorldNode *scene =
    //worldnode.load(stream)
    PLOGI << "Loading scene " << filePath;
    Stream stream(filePath, READ_MODE);

    //assume the first element in the scene is always a world node
    WorldNode* newScene = new WorldNode(1.0, 1.0, 1.0, 1.0);
    v_scenes.push_back(newScene);
    newScene->load(stream);
}




void AssetManager::saveScene(string filePath) 
{

    Stream stream(filePath, WRITE_MODE);
    currentScene->save(stream);


}


void AssetManager::loadShader(string vpath, string fpath, string name)
{
    Shader *shader = new Shader(vpath.c_str(), fpath.c_str());
    shader->SetName(name);
    shaders[name] = shader;
    v_shaders.push_back(shader);
}
Model* AssetManager::getModel(const string name)
{
    return models[name];
}


const vector<Model*>& AssetManager::getModels() const
{
    return v_models;
}


const vector<Node*>& AssetManager::getScenes() const
{
    return v_scenes;
}


const vector<Shader*>& AssetManager::getShaders() const
{
    return v_shaders;
}

void AssetManager::addScene(Node* scene) 
{
    if (scene)
        v_scenes.push_back(scene);
    else
        PLOGE << "Tried to add a null scene";
}

void AssetManager::setCurrentScene( Node* scene)
{
    if (scene != 0)
        currentScene = scene;
    else 
        PLOGE << "Trying to make current scene null";
}

Node* AssetManager::getCurrentScene() 
{
    return currentScene;
}


void AssetManager::createFrameBuffer(int width, int height, string name)
{
    if(frameBuffers.count(name) > 0)
    {
        FrameBuffer* fb = new FrameBuffer(width, height);
        v_frameBuffers.push_back(fb);
        std::ostringstream oss;
        oss << name <<fb->GetID();
        string newName = oss.str();
        
        fb->SetName(newName);
        frameBuffers[newName] = fb;
    }
    else
    {
        FrameBuffer* fb = new FrameBuffer(width, height);
        v_frameBuffers.push_back(fb);
        fb->SetName(name);
        frameBuffers[name] = fb;
    
    }

}



void AssetManager::createScreenCanvas(int width, int height, string name)
{
    if (screenCanavases.count(name) > 0)
    {
        ScreenCanvas* sc = new ScreenCanvas(width, height);
        v_ScreenCanvases.push_back(sc);
        std::ostringstream oss;
        oss << name << sc->GetID();
        string newName = oss.str();

        sc->SetName(newName);
        screenCanavases[newName] = sc;
    }
    else
    {
        ScreenCanvas* sc = new ScreenCanvas(width, height);
        v_ScreenCanvases.push_back(sc);
        sc->SetName(name);
        screenCanavases[name] = sc;

    }

}

const vector<ScreenCanvas*>& AssetManager::getScreenCanvases() const 
{
    return  v_ScreenCanvases;
}


FrameBuffer* AssetManager::getFrameBuffer(string name)
{
    return frameBuffers[name];
}


const vector<FrameBuffer*>& AssetManager::getFrameBuffers() const
{
    return v_frameBuffers;
}

FrameBuffer *AssetManager::getCurrentFrameBuffer()
{
    return currentFrameBuffer;
}

void AssetManager::makeBufferCurrent(FrameBuffer *buffer)
{
    if(buffer)
    currentFrameBuffer = buffer;
    else
    PLOGE<<"TRYING TO MAKE CURRENT FRAMEBUFFER NULL BUFFER NAME "<< buffer->GetName();
}

void  AssetManager::recreateMainFB(int width, int height)
{
    PLOGE<<"RECREATED MAIN FB";
    mainBuffer->recreate(width, height);
}


FrameBuffer* AssetManager::getMainBuffer()
{
    if(mainBuffer)
    return mainBuffer;
    else
    PLOGE<<"TRYING TO ACCESS MAIN FB BEFORE ITS CREATION";
    return nullptr;
}

void AssetManager::createmainFB(int width, int height)
{
    if(mainBuffer)
    {mainBuffer = new FrameBuffer(width, height);
    PLOGE<<"CREATED MAIN FB";
    }
    else
    PLOGE<<"TRYING TO RECREATE MAIN FB BEFORE ITS CREATION";
}

void AssetManager::getDefault(const Rtti &type, Node *parent)
{
    //start with animated Node
    //then Node
    //model node
}

void AssetManager::registerAction(Action* action) 
{
    switch (action->m_at) {
    case KEY:
        KeyActionsVector.push_back(action);
        break;
    case MOUSE:
        MouseActionsVector.push_back(action);
        break;
    case ALL:
        KeyActionsVector.push_back(action);
        MouseActionsVector.push_back(action);
        break;
    default:
        break;
    }
}
