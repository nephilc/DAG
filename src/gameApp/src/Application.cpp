#include "Application.hpp"
#include <iostream>
#include <plog/Log.h>
#include <cassert>
#include<NodeFactory.hpp>
Application *Application::application = nullptr;

InputDevice Application::inputDevice = KEYBOARD_MOUSE;

//when resizing we need to create a new framebuffer with different dimensions.
//
//mesh instance object-
//the instance object types.
//draw state enum

//no need to recreate the framebuffer, for now. ONe need to fix the camera projection, on resizing the rendering window.
//could do it later.
/*
unsigned int Application::framebuffer = 0;
unsigned int Application::textureColorbuffer = 1;
unsigned int Application::rbo = 0;
*/
glm::mat4 Application::model = glm::mat4(1.0f);
glm::mat4 Application::idm = glm::mat4(1.0f);
//FrameBuffer* Application::m_FB = 0;

Camera* Application::camera = 0;

//TODO: Maybe, i'll make all modules static
bool Application::firstMouse = true;
float Application::lastX = 100.0f;//place holder values
float Application::lastY = 100.0f;
int Application::m_iWidth = 600;
int Application::m_iHeight = 800;
input_mode Application::imode = EDITOR;
GLFWwindow *Application::m_window = 0;
int Application::m_iFrameWidth = 600;
int Application::m_iFrameHeight = 800;

Application::Application 
        (const char* acWindowTitle, int iXPosition,
        int iYPosition, int iWidth, int iHeight): m_acWindowTitle(acWindowTitle), 
        m_iXPosition(iXPosition), m_iYPosition(iYPosition)/*, m_iWidth(iWidth), m_iHeight(iHeight)*/    
{
    lastX = m_iWidth / 2.0f;
    lastY = m_iHeight / 2.0f;         
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    

    PLOGI<<"EDITOR APPLICATION:: ENGINE VERSION "/*<<ENGINE10_VERSION_MAJOR <<"."<< ENGINE10_VERSION_MINOR*/;
    //PLOGD<<"CALLING APPLICATION CONSTRUCTOR";
}

Application *Application::getApplication(const char *acWindowTitle, int iXPosition, int iYPosition, int iWidth, int iHeight)
{
    if(!application)
    {
        application = new Application(acWindowTitle,  iXPosition,  iYPosition, iWidth, iHeight);
        application->init();
    }
    return application;
}

AssetManager* Application::getAssetManager() { return assetManager; }

Application *Application::getApplication()
{
    assert(application!=nullptr);   
    return application;
}

Application ::~Application()
{
    PLOGI<<"EXECUTING APP DESTRUCTOR";
    deallocateModules();
    terminate();
}


void Application::init()
{
    PLOGI<<"INITIALIZINNG THE APPLICATION";
    specifyContext();
    createWindow();
    passCallbacks();
    loadGL();
    allocateModules();
    //m_FB = new FrameBuffer(m_iWidth, m_iHeight);
    PLOGD<<"allocated modules";
    populateScanCodeMap();//make sure to call this after module allocation
    populateGamePadMap();
    populateAxesVector();
    NodeFactory::init();
    //AnimatedNode::initAnimator();


}
//since the code and the character are different
//ill workk with just the characters, and get the key from within
//it is a map i can create on my own
//whe i want to call an action i will call it with the 
//^put all the kays in a vector
void Application::populateScanCodeMap() {
    //or fill up the vector first, then fill up the map automatically, but well.

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (char c : alphabet) {
        //assetManager->charActionMap[std::string(1, c)] = string("NO ACTION");

        //PLOGD << c << " : " << assetManager->charActionMap[std::string(1, c)];
        assetManager->keyBoardVector.push_back(std::string(1, c));

    }
    for (int i = 0; i <= 9; i++) 
    {
        //assetManager->charActionMap[to_string(i)] = string("NO ACTION");

        //PLOGD << i << " : " << assetManager->charActionMap[to_string(i)];
        assetManager->keyBoardVector.push_back(to_string(i));

        
    }
    assetManager->keyBoardVector.push_back("space");
    assetManager->keyBoardVector.push_back("escape");
    assetManager->keyBoardVector.push_back("enter");
    assetManager->keyBoardVector.push_back("tab");
    assetManager->keyBoardVector.push_back("shift left");
    assetManager->keyBoardVector.push_back("Caps Lock");
    assetManager->keyBoardVector.push_back("up");
    assetManager->keyBoardVector.push_back("down");
    assetManager->keyBoardVector.push_back("left");
    assetManager->keyBoardVector.push_back("right");
    for (string& key : assetManager->keyBoardVector) {
        //assetManager->KeyboardActionMap[key] = Action::NoAction;
    }

    assetManager->MouseVector.push_back("Mouse Left");
    assetManager->MouseVector.push_back("Mouse Right");
    assetManager->MouseVector.push_back("Mouse Cursor");
    for (string& key : assetManager->MouseVector) {
        //assetManager->MouseActionMap[key] = Action::NoAction;
    }

/*
    for (const auto& action : assetManager->KeyboardActionMap) {

        PLOGD << action.first << ": " << action.second->GetName() << endl;
    }
  */
   assetManager->KeyActionsVector.push_back(new Action("test Action"));
    assetManager->KeyActionsVector.push_back(Action::NoAction);

    assetManager->MouseActionsVector.push_back(new Action("test Action"));
    assetManager->MouseActionsVector.push_back(Action::NoAction);
    //keysPressed = new std::vector<std::string>
      //  ((assetManager->keyBoardVector.size() + assetManager->MouseVector.size() + assetManager->GamePadVector.size()));

}

void Application::populateGamePadMap() 
{
    GLFWGamePadMapping[0] = "A";
    GLFWGamePadMapping[1] =  "B";
    GLFWGamePadMapping[2] =  "X";
    GLFWGamePadMapping[3] =  "Y";
    GLFWGamePadMapping[4] = "LEFT_BUMPER";
    GLFWGamePadMapping[5] = "RIGHT_BUMPER";
    GLFWGamePadMapping[6] = "BACK";
    GLFWGamePadMapping[7] = "START";
    GLFWGamePadMapping[8] = "GUIDE";
    GLFWGamePadMapping[9] = "LEFT_THUMB";
    GLFWGamePadMapping[10] = "RIGHT_THUMB";
    GLFWGamePadMapping[11] = "DPAD_UP";
    GLFWGamePadMapping[12] = "DPAD_RIGHT";
    GLFWGamePadMapping[13] = "DPAD_DOWN";
    GLFWGamePadMapping[14] = "DPAD_LEFT";
}

void Application::populateAxesVector()
{
    GLFW_Axes_Vector.push_back("AXES_0_1");
    GLFW_Axes_Vector.push_back("AXES_2_3");
    GLFW_Axes_Vector.push_back("AXES_4");
    GLFW_Axes_Vector.push_back("AXES_5");
}


void Application::allocateModules()
{
    assert(application!=nullptr);
    //for some reason the application pointer doesnt get update above
    assetManager = AssetManager::getInstance();
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));


}

void Application::deallocateModules()
{   delete camera;
    delete assetManager;
    
}

void Application::getIMode()
{

}

void Application::loopEnd()
{

}


void Application::loopContent()
{
    
 
}