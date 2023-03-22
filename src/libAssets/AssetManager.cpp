#include "AssetManager.hpp"
#include <plog/Log.h>

FrameBuffer* AssetManager::mainBuffer = 0;
AssetManager::AssetManager(/* args */)
{
    PLOGI<<"CREATING ASSETMANAGER";
    mainBuffer = new FrameBuffer(800, 600);
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
    
}

AssetManager::~AssetManager()
{
    PLOGI<<"DESTROYING ASSETMANAGER";
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


void AssetManager::loadScene(string path, string name)
{
    if(models.count(name) > 0)
    {
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
