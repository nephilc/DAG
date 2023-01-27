#include "AssetManager.hpp"
#include <plog/Log.h>

FrameBuffer* AssetManager::mainBuffer = 0;
AssetManager::AssetManager(/* args */)
{
    PLOGI<<"CREATING ASSETMANAGER";
}

AssetManager::~AssetManager()
{
    PLOGI<<"DESTROYING ASSETMANAGER";
}


void AssetManager::loadModel(string path, string name)
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


FrameBuffer* AssetManager::getFrameBuffer(string name)
{
    return frameBuffers[name];
}

const vector<FrameBuffer*>& AssetManager::getFrameBuffers() const
{
    return v_frameBuffers;
}


void  AssetManager::recreateMainFB(int width, int height)
{
    PLOGE<<"RECREATED MAIN FB";
    mainBuffer->recreate(width, height);
}


FrameBuffer* AssetManager::getMainBuffer()
{
    return mainBuffer;
}

void AssetManager::createmainFB(int width, int height)
{
    mainBuffer = new FrameBuffer(width, height);
    PLOGE<<"CREATED MAIN FB";
}

void AssetManager::getDefault(const Rtti &type, Node *parent)
{
    //start with animated Node
    //then Node
    //model node
}
