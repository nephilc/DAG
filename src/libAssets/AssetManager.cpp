#include "AssetManager.hpp"
#include <plog/Log.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

FrameBuffer* AssetManager::mainBuffer = 0;
std::string AssetManager::configFile= "xdg.cfg";

std::string AssetManager::noValue = "noValue";//no value placeholder when saving or loading

std::string AssetManager::kmDBFile = "common/KM/db.kmf";//no value placeholder when saving or loading


Action* AssetManager::getKeyAction(std::string actionName)
{
    for (Action* action : KeyActionsVector) 
    {
        if (action->GetName() == actionName) return action;
    }
    PLOGE << "ACTION NOT FOUND " << actionName;
    return new Action();
}

Action* AssetManager::getMouseAction(std::string actionName)
{
    for (Action* action : MouseActionsVector)
    {
        if (action->GetName() == actionName) return action;
    }
    PLOGE << "ACTION NOT FOUND " << actionName;
    return new Action();
}

AssetManager::AssetManager(/* args */)
{
    PLOGI<<"CREATING ASSETMANAGER";
    mainBuffer = new FrameBuffer(1280, 720);//the resolution of the framebuffer will determine the quality of the image
    v_frameBuffers.push_back(mainBuffer);
    Stream stream(configFile, READ_MODE);
    //read the entire configuration file into a map    
    if(stream.isOpen())
    {
        string pathLine = stream.readln();
        std::stringstream ss(pathLine);
        while (std::getline(ss, basePath, '=')) 
        {
            continue;
        }
    }

    if(basePath=="") PLOGE<<"CONFIGATION FILE NOT READ PROPERLY";
    PLOGI<<"FILE://   <=>  "<< basePath; 


    makeBufferCurrent(mainBuffer);
    //CreateDefaults();

}



void AssetManager::CreateDefaults()
{
    PLOGI<<"CREATING DEFAULTS";
    //should put these in a config file
    loadShader("shaderPrograms/animation.vs", "shaderPrograms/1.model_loading.fs", "ourShader1");
    loadShader("shaderPrograms/1.model_loading.vs", "shaderPrograms/1.model_loading.fs", "ourShader2");
    //loadModel("3dmodels/anotherone.fbx");

    defaultShader = getShaders()[1];
    defaultAniShader = getShaders()[0];

    /*
//    defaultModel = getModel("arissa");
    defaultModel = v_models[0];
    //loadAnimation("3dmodels/anotherone.fbx", defaultModel);
    defaultAnimation = v_Animations[0];
    defaultAnimator = new Animator(defaultAnimation);
    defaultaniNode = new AnimatedNode(defaultModel, defaultAniShader, defaultAnimation);
    */
    //#################These would be dafault action maps
    //currentMouseActionMap = &MouseActionMap;
    //currentKeyboardActionMap = &KeyboardActionMap;
    //currentGamePadActionMap = &GamePadActionMap;
    currentKeyboardKeyMap = nullptr;
    currentMouseKeyMap = nullptr;
    currentGamepadKeyMap = nullptr;
    currentAxesKeyMap = nullptr;
}

AssetManager::~AssetManager()
{
    PLOGI<<"DESTROYING ASSETMANAGER";
}
ScreenCanvas* AssetManager::getScreenCanvas(const string name)
{
    return screenCanavases[name];
}

Model* AssetManager::loadModel(string path)//map filename to pointer, having two params may be redundant but the method can be repurposed
{
    string fileName;
    std::stringstream ss(path);
     while (std::getline(ss, fileName, '/')) {
        continue;
    }
    bool shouldLoad = false;
    std::cout<<fileName<<std::endl;
    if (models.count(fileName) > 0) {
        Model *foundModel = models[fileName];
        if(foundModel->path != path)
        { 
            PLOGE<<"Thes two models have the same file name but different paths, they should have different fileNames";
            PLOGE<<path;
            PLOGE<<foundModel->path;
            return nullptr;
        }
        PLOGI<<fileName<<" Already Exists";
        return foundModel;

        
    }
    else 
    {
        Model* model = Model::loadModel(path, fileName);
        if (model!= nullptr)
        {
            models[fileName] = model;
            model->SetName(fileName);
            v_models.push_back(model);
            return model;

            //if name already exists append the object id to it.
            /*
            std::ostringstream oss;
            oss << fileName << model->GetID();
            string newName = oss.str();
            models[newName] = model;
            model->SetName(newName);
            v_models.push_back(model);
            */
        }
        else 
        {
            PLOGE << "FAILED TO LOAD MODEL AT" << path;
            return nullptr;
        }

            
    }
}

std::string AssetManager::getSplitPathUsingBasePath(const string& fullPath) 
{
    string relativePath;
    string part;
    bool record = false;
    std::stringstream ss(fullPath);
    while (std::getline(ss, part, '/')) {
        if (record) {
            if (!relativePath.empty()) {
                relativePath += "/";
                relativePath += part;
            }
            else {
                relativePath += part;
            }
        }
        if (part == basePath) record = true;

    }
    if(record)
        return relativePath;
    else
        return fullPath;
}
Model* AssetManager::loadModel(Stream &stream) 
{
    string typeName = stream.readln();//model type read
    if (typeName == noValue) return nullptr;

    string relativePath = stream.readln();
    Model* loadedModel = loadModel(basePath + "/" + relativePath);
    loadedModel->load(stream);

    return loadedModel;
}
Animation* AssetManager::loadAnimation(string vpath, Model* model)
{
    Animation* animation = Animation::loadAnimation(basePath + "/" + vpath, model);
    if (animation != nullptr) v_Animations.push_back(animation);
    else PLOGE << "CAnnot load ANimation AT" << vpath;
    return animation;
}
Animation* AssetManager::loadAnimation(Stream& stream, Model* model)
{
    //we should be able to load an animation without a model, that was just a malformation in those mixamo models.
    //we should remove that read missingbone data since we have no missing bone data.
    string animationType = stream.readln();

    if (animationType == noValue) return nullptr;
    string relativePath = stream.readln();
    if (model == nullptr) {
        PLOGE << "FOR NOW WE CANNOT LOAD ANIMATION WITHOUT MODEL";
        Animation* animation = new Animation();
        animation->load(stream);//just to clear the object properties.
        return nullptr;
    }
    
    Animation* animation = loadAnimation(relativePath, model);
    animation->load(stream);
    return animation;
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
    setCurrentScene(newScene);
}

void AssetManager::loadKeyMap(string fullPath) 
{
    string path = getSplitPathUsingBasePath(fullPath);
    Stream stream(basePath+"/"+ path, READ_MODE);

    KeyMap *km = new KeyMap();
    km->load(stream);
    KeyMapsVector.push_back(km);
    
}

//create another version where you pass the key map and saves it in the same file, specified in the file attribute
void AssetManager::saveKeyMap(string fullPath, KeyMap *km, string fileName, bool trunc)
{//well this function  will only be used in the editor, dont have to use Stream

    if (!trunc) {
        updateKeymapDBFile(km, fileName);
        km->setFileName(fileName);


        string path = getSplitPathUsingBasePath(fullPath);
        Stream stream(basePath + "/" + path, WRITE_MODE);
        if (stream.isOpen())
            km->save(stream);
    }
    else {
        Stream stream(basePath + "/" +"common/KM/"+ km->getFileName(), TRUNC_MODE);
        if (stream.isOpen())
            km->save(stream);
    }
    //update db file "db.kmf"
    //either you want to change the map fileName  or first time saving the map
    //in this case you can just append to the db and remove the old file if km.fileName!=""
}


void AssetManager::updateKeymapDBFile(KeyMap* km, string newFile)
{
    std::fstream inputFile(basePath+"/"+kmDBFile, std::ios::in);
    if (!inputFile) {
        std::cerr << "Failed to open input file." << std::endl;
        return ;
    }

    std::ofstream tempFile(basePath+"/"+"common/KM/temp.txt");
    if (!tempFile) {
        std::cerr << "Failed to open temporary file." << std::endl;
        return ;
    }
    std::vector<std::string> lines;

    std::string line;

    while (std::getline(inputFile, line)) {
        PLOGD << "comparing " << line << "  " << km->getFileName();
        if (line != km->getFileName()) {
            lines.push_back(line);
        }
    }
    inputFile.close();

    inputFile.open(basePath + "/" + kmDBFile, std::ios::out | std::ios::trunc);
    if (!inputFile) {
        std::cerr << "Failed to open input file for writing." << std::endl;
        return ;
    }

    for (const std::string& modifiedLine : lines) {
        inputFile << modifiedLine << std::endl;
    }
    inputFile << newFile;

    inputFile.close();
    tempFile.close();
    std::string tempFileName = basePath + "/" + "common/KM/temp.txt";
    if (!km->getFileName().empty())
    {
        string fileToDelete = basePath + "/" + "common/KM/" + km->getFileName();
        if (remove(fileToDelete.c_str()) != 0) {
            std::cerr << "Error deleting OLD FILE " << std::endl;
        }
    }

    if (remove(tempFileName.c_str()) != 0) {
        std::cerr << "Error deleting temporary file." << std::endl;
    }

}
void AssetManager::saveScene(string filePath) 
{

    Stream stream(filePath, WRITE_MODE);
    currentScene->save(stream);


}

AssetManager* AssetManager::am = nullptr;

AssetManager* AssetManager::getInstance()
{
    if(am == nullptr) 
    {
        am = new AssetManager();
        return am;
    }
    else return am;
}

Shader* AssetManager::loadShader(string vpath, string fpath, string namesConcat)
{
    bool shouldLoad = false;
    std::cout<<namesConcat<<std::endl;
    if (shaders.count(namesConcat) > 0) {
        Shader *foundShader = shaders[namesConcat];
        if(foundShader->m_vertexPath != vpath || foundShader->m_fragmentPath != fpath)
        { 
            PLOGE<<"Thes two programs have the same Code name but different paths, Duplicate filenames for the same kind of files should be removed";
            PLOGE<<vpath;
            PLOGE<<fpath;
            return nullptr;
        }
        PLOGI<<namesConcat<<" Already Exists";
        return foundShader;

        
    }
    else 
    {
        Shader *shader = new Shader(vpath.c_str(), fpath.c_str());
        if (shader!= nullptr)
        {
            shaders[namesConcat] = shader;
            shader->SetName(namesConcat);
            shaders[namesConcat] = shader;
            v_shaders.push_back(shader);
            return shader;

            //if name already exists append the object id to it.
            /*
            std::ostringstream oss;
            oss << fileName << model->GetID();
            string newName = oss.str();
            models[newName] = model;
            model->SetName(newName);
            v_models.push_back(model);
            */
        }
        else 
        {
            PLOGE << "FAILED TO LOAD SHADER AT" << namesConcat;
            return nullptr;
        }

            
    }
    
}

Shader* AssetManager::loadShader(Stream &stream)
{
    string shaderType = stream.readln();

    if (shaderType == noValue) return nullptr;

    string concat = stream.readln();
    string vpath = stream.readln();
    string fpath = stream.readln();
    //string vfileName = fileNameFromPath(vpath);
    //string ffileName = fileNameFromPath(fpath);
    //string concat = vfileName+ffileName;
    //string shaderType = stream.readln();
    Shader* shader = loadShader(vpath, fpath, concat);
    shader->load(stream);//dont need to override the shader load, call the objects load directly
    shader->SetName(concat);
    return shader;
}




Shader* AssetManager::loadShader(string vpath, string fpath)
{
    string vfileName = fileNameFromPath(vpath);
    string ffileName = fileNameFromPath(fpath);
    string concat = vfileName+ffileName;
    Shader* shader = loadShader(vpath, fpath, concat);
 //   shader->load(stream);//dont need to override the shader load, call the objects load directly
    return shader;
}



std::string AssetManager::fileNameFromPath(std::string path)
{
    string fileName;
    std::stringstream ss(path);
     while (std::getline(ss, fileName, '/')) {
        continue;
    }
    return fileName;
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

const vector<Animation*>& AssetManager::getAnimations() const 
{
    return v_Animations;
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

void AssetManager::createKeyMap()
{
    KeyMapsVector.push_back(new KeyMap(KEYBOARD_MAP));
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
    case AXES:
        AxesActionsVector.push_back(action);
        break;
    case ALL:
        KeyActionsVector.push_back(action);
        MouseActionsVector.push_back(action);
        AxesActionsVector.push_back(action);
        break;
    default:
        break;
    }
}


void AssetManager::setCurrentKeyMap(KeyMap* keyMap)
{
    //currentKeyMap=keyMap;
}
KeyMap* AssetManager::getCurrentKeyMap()
{
    return nullptr;
}
