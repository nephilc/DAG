#include "Application.hpp"
#include <iostream>
#include <plog/Log.h>


//when resizing we need to create a new framebuffer with different dimensions.
//
//mesh instance object
//the instance object types.
//draw state enum

//no need to recreate the framebuffer, for now. ONe need to fix the camera projection, on resizing the rendering window.
//could do it later.
unsigned int Application::framebuffer = 0;
unsigned int Application::textureColorbuffer = 0;
unsigned int Application::rbo = 0;

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

Application ::~Application ()
{
//    PLOGI<<"EXECUTED APP DESTRUCTOR";
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
}

void Application::allocateModules()
{

}

void Application::deallocateModules()
{   
    
}


void Application::createWindow()
{
    m_window = glfwCreateWindow(m_iWidth, m_iHeight, m_acWindowTitle, /*glfwGetPrimaryMonitor()*/ NULL, NULL);
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
}
int Application::Main (int iQuantity, char** apcArgument)
{

    while (!glfwWindowShouldClose(m_window))
    {

        glEnable(GL_DEPTH_TEST);    
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
    return 0;
}
int Application::processInput()
{
	if(imode == WORLD)
	{  
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS);
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
    glViewport(0, 0, width, height);
    m_iWidth = width;
    m_iHeight = height;
    

}


void Application::resizeViewport(int width, int height)
{
    glViewport(0, 0, width, height);
    //m_iWidth = width;
    //m_iHeight = height;

}

//the editor will get the imode from the application and update itself
void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_TAB && action == GLFW_PRESS)
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
	if(imode == WORLD)
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
    //camera->ProcessMouseMovement(xoffset, yoffset);
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


std::string Application::utf8chr(int cp)
{
    char c[5]={ 0x00,0x00,0x00,0x00,0x00 };
    if     (cp<=0x7F) { c[0] = cp;  }
    else if(cp<=0x7FF) { c[0] = (cp>>6)+192; c[1] = (cp&63)+128; }
    else if(0xd800<=cp && cp<=0xdfff) {} //invalid block of utf8
    else if(cp<=0xFFFF) { c[0] = (cp>>12)+224; c[1]= ((cp>>6)&63)+128; c[2]=(cp&63)+128; }
    else if(cp<=0x10FFFF) { c[0] = (cp>>18)+240; c[1] = ((cp>>12)&63)+128; c[2] = ((cp>>6)&63)+128; c[3]=(cp&63)+128; }
    return std::string(c);
}


/*
void Application::renderDock()
{
bool open = true;

ImGui::Begin("docking window", &open);
//ImGui::SetWindowSize(ImVec2(600, 600));

ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
ImGui::DockSpace(dockspace_id);



ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
ImGuiWindowFlags window_flags = ImGuiWindowFlags_UnsavedDocument;

ImGui::Begin("dock test", &open, window_flags);
ImGui::SetWindowSize(ImVec2(600, 600));

ImGui::End();

ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
ImGuiWindowFlags window_flags1 = ImGuiWindowFlags_UnsavedDocument;

ImGui::Begin("child window", &open, window_flags1);
ImGui::SetWindowSize(ImVec2(600, 600));

ImGui::End();

ImGui::End();
  
}
*/

void Application::getIMode()
{

}

void Application::loopEnd()
{

}


void Application::loopContent()
{
    
 
}