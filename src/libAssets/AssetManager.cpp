#include "AssetManager.hpp"
#include <plog/Log.h>


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
