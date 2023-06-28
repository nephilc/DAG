#include<Application.hpp>
#include <plog/Log.h>


void Application::createWindow()
{
    //const GLFWvidmode* mode = glfwGetVideoMode(monitor);
     GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    m_window = glfwCreateWindow(mode->width, mode->height, m_acWindowTitle, /*glfwGetPrimaryMonitor()*/ NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        //return -1;
    }
    glfwMakeContextCurrent(m_window);
    
    //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


}
void Application::specifyContext()
{
    /* Initialize the library */
    if(!glfwInit()) PLOGE<<"FAILED TO INITIALIZE GLFW";


    //glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}
void Application::loadGL()
{

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
         PLOGE<<"FAILED TO INITIALIZE GLAD";
    }    
    glfwSwapInterval(1);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}
void Application::passCallbacks()
{
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSetKeyCallback(m_window, key_callback);
    glfwSetCharCallback(m_window, character_callback);
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
    glfwSetCursorEnterCallback(m_window, cursor_enter_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwSetScrollCallback(m_window, scroll_callback);
    glfwSetDropCallback(m_window, drop_callback);
    glfwSetJoystickCallback(joystickCallback);
    
}
int Application::processInput()
{
    /*
	if (glfwGetKey(m_window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
	   if (imode == WORLD)
	   { 
	   	imode = EDITOR;
	   	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	   	
	   }
	   else{ 
	   imode = WORLD;
	   glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	   
	   }
	}
*/	 

	if(imode ==WORLD){
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
    }


    return 0;
}  


int Application::terminate()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
    
    PLOGD<<"EXECUTED APPLICATION DESTRUCTOR";
    return 0;
}

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    //glViewport(0, 0, width, height);
    glViewport(0, 0, m_iWidth, m_iHeight);
    m_iWidth = m_iFrameWidth ;//these are for the camera
    m_iHeight = m_iFrameHeight ;
    PLOGD<<width <<" " <<height;
    PLOGD<<m_iWidth <<"   ii " <<m_iHeight;

    //m_FB->recreate(width, height);//this is the one we render to
    //AssetManager::getMainBuffer()->recreate(m_iWidth, m_iHeight);
    //i think the framebuffer callback is called on the currently bound framebuffer.    

}


void Application::resizeViewport(int width, int height)
{
    //glViewport(0, 0, width, height);
    //m_iWidth = width;
    //m_iHeight = height;
    //assetManager->recreateMainFB(m_iFrameWidth, m_iFrameHeight);
    PLOGD << m_iFrameWidth;

}    
void Application::handleKeys(std::string key, float time_of_event) 
{
    key_event event = { key, time_of_event };
    unhandled_keys.push(event);
    
}
void Application::handle_input(float current)
{
    //Anything that should happen "when the users presses the key" should happen here
    while (!unhandled_keys.empty()) {
        key_event event = unhandled_keys.front();
        unhandled_keys.pop();
        if (application->getAssetManager()->currentMouseKeyMap != 0) {
            float dt1 = current - event.time_of_event;
            application->getAssetManager()->currentKeyboardKeyMap->get(event.key)->KeyAction(current);
            PLOGD << dt1 << "time";
        }
    }
    //Anything that should happen "while the key is held down" should happen here.
}
void Application::addKeyPressed(std::string key)
{
    keysPressed.push_back(key);
}
void Application::removeKeyPressed(std::string key)
{
    keysPressed.remove(key);
}
//the editor will get the imode from the application and update itself
void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
        if (imode == SIMULATION && action==GLFW_PRESS)
        {


            const char* pressedName = glfwGetKeyName(key, scancode);
            if (pressedName != 0 && -1 <= *pressedName && *pressedName <= 255 && isalpha(*pressedName))
            {
                std::string keyString = std::string(pressedName);
                Application::getApplication()->addKeyPressed(keyString);
                //if (application->getAssetManager()->cur/rentMouseActionMap != 0)
                    //application->getAssetManager()->cur/rentKeyboardActionMap->at(keyString)->KeyAction(application->deltaTime);
                //application->getApplication()->handleKeys(keyString, (float)glfwGetTime());
                //application->getApplication()->keysPressed->push_back(keyString);
                

            }
            if (key <= GLFW_KEY_KP_9 && key >= GLFW_KEY_KP_0)
            {
                std::string keyString = to_string(key - GLFW_KEY_KP_0);
                Application::getApplication()->addKeyPressed(keyString);


            }

            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
            {
                imode = EDITOR;
                application->enableCursor();
                editorUI->updateInputFlags(EDITOR);

            }

     }
        else  if (imode == SIMULATION && action == GLFW_RELEASE) {
            const char* pressedName = glfwGetKeyName(key, scancode);
            if (pressedName != 0 && -1 <= *pressedName && *pressedName <= 255 && isalpha(*pressedName))
            {
                std::string keyString = std::string(pressedName);
                Application::getApplication()->removeKeyPressed(keyString);
                //if (application->getAssetManager()->cur/rentMouseActionMap != 0)
                    //application->getAssetManager()->cur/rentKeyboardActionMap->at(keyString)->KeyAction(application->deltaTime);
                //application->getApplication()->handleKeys(keyString, (float)glfwGetTime());
                //application->getApplication()->keysPressed->push_back(keyString);


            }
            if (key <= GLFW_KEY_KP_9 && key >= GLFW_KEY_KP_0)
            {
                std::string keyString = to_string(key - GLFW_KEY_KP_0);
                Application::getApplication()->removeKeyPressed(keyString);


            }


        }
            

     if (imode == WORLD)
     {
        switch (action)
        {
        case GLFW_PRESS:
            //PLOGD<<"KEY CALLBACK WITH KEY CODE "<<  glfwGetKeyName(key, 0) << " ACTION PRESS" ;
            break;
        case GLFW_RELEASE:
            //PLOGD<<"KEY CALLBACK WITH KEY CODE "<<  glfwGetKeyName(key, 0) << " ACTION RELEASE";
            break;
        case GLFW_REPEAT:
            //PLOGD<<"KEY CALLBACK WITH KEY CODE "<<  glfwGetKeyName(key, 0) << " ACTION REPEAT";
            break;
        default:
            break;
        }
    }


    //pass press to the action functions as a parametre

	if(key == GLFW_KEY_TAB && action == GLFW_PRESS && imode!=SIMULATION)
 	{

	   if (imode == WORLD)
	   { 
	   	imode = EDITOR;
	   	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);	   	
        editorUI->updateInputFlags(imode);

	   }
	   else{ 
        
	   imode = WORLD;
	   glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	    editorUI->updateInputFlags(imode);

	   }
	}

}

void Application::disableCursor(){
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Application::enableCursor(){
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Application::character_callback(GLFWwindow* window, unsigned int codepoint)
{
        //PLOGD<<"CHARACTER CALLBACK   "<<  utf8chr(codepoint);

}

//well, the camera pointer can be static. and all these state variables relatif to the mouse
//can be static aswell.
void Application::cursor_position_callback(GLFWwindow* window,  double xposIn, double yposIn)
{
    //PLOGD<<"CURSOR POSITION CALLBACK xpos:"<< xposIn  << " ypos : " <<yposIn;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
	
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
    if(imode == WORLD)
	{
    camera->ProcessMouseMovement(xoffset, yoffset);
	}
    else if (imode == SIMULATION)
    {
        if(application->getAssetManager()->currentMouseKeyMap!=nullptr)
        application->getAssetManager()->currentMouseKeyMap->get("Mouse Cursor")->MouseAction(xposIn, yposIn, xoffset, yoffset);
    }

}

void Application::cursor_enter_callback(GLFWwindow* window, int entered)
{
    //PLOGD<<"CURSO ENTER CALLBACK";
    if (entered)
    {
        // The cursor entered the content area of the window
    }
    else
    {
        // The cursor left the content area of the window
    }
}

void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(imode == EDITOR)
    {
    //PLOGD<<"MOUSE BUTTON CALLBACK";
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        //PLOGD<<"MOUSE BUTTON RIGHT";
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        //PLOGD<<"MOUSE BUTTON LEFT";
    }
    
    switch (action)
    {
    case GLFW_PRESS:
        //PLOGD<<"MOUSE BUTTON  "<<  " " << " ACTION PRESS" ;
        break;
    case GLFW_RELEASE:
        //PLOGD<<"MOUSE BUTTON  "<<  " " << " ACTION RELEASE";
        break;
    case GLFW_REPEAT:
        //PLOGD<<"MOUSE BUTTON  "<<  " " << " ACTION REPEAT";
        break;
    default:
        break;
    }
    }
    
}

void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(imode != EDITOR)
    {
    //PLOGD<<"SCROLL CALLBACK xoffset : "<< xoffset<<" yoffset : " << yoffset;
    //camera->ProcessMouseScroll(static_cast<float>(yoffset));
    }
}

void Application::drop_callback(GLFWwindow* window, int count, const char** paths)
{
    PLOGD<<"PATH DROP";
    int i;
    for (i = 0;  i < count;  i++)
    {
        PLOGD<<paths[i];

    }
}



void Application::joystickCallback(int jid, int event)
{
    if (event == GLFW_CONNECTED) {
        std::cout << "Joystick connected: " << glfwGetJoystickName(jid) << std::endl;
    } else if (event == GLFW_DISCONNECTED) {
        std::cout << "Joystick disconnected: " << glfwGetJoystickName(jid) << std::endl;
    }
}