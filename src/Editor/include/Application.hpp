#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include <EditorUI.hpp>


#include <string>
#include<AssetManager.hpp>
#include<Mesh.hpp>
#include<Camera.hpp>
#include <animator.h>
#include <AnimatedNode.hpp>
//#include <__msvc_chrono.hpp>
#include <queue>
#include<map>


enum input_mode
{

EDITOR,
WORLD,
SIMULATION

};
struct key_event {
    std::string key;
    float time_of_event;
};

enum InputDevice {
    GAMEPAD,
    KEYBOARD_MOUSE
};

class Application
{
friend class EditorUI;
private:
    static Application *application;
    static EditorUI *editorUI;
    const char* m_acWindowTitle;//does it have to be constant.
    int m_iXPosition, m_iYPosition;
    static int m_iWidth, m_iHeight;
    static int m_iFrameWidth, m_iFrameHeight;

    static GLFWwindow *m_window;
    int m_iWindowID;
    double m_dTime, m_dDeltaTime;
    static float lastX ;
    static float lastY ;
    static bool firstMouse;

    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    static input_mode imode;

    static InputDevice inputDevice;
   
    map<int, string> GLFWGamePadMapping;
    
    std::vector<string> GLFW_Axes_Vector;


    //then this camera should be in the editor class.
    //or in the asset manager, this is a free camera not tied to a node
    static Camera *camera;//this is the editor's camera, not the games camera or whatever software to build on top of the engine
    AssetManager *assetManager;
    void populateScanCodeMap();

/*
    static unsigned int framebuffer;
    static unsigned int textureColorbuffer;
    static unsigned int rbo;
    unsigned int quadVAO, quadVBO;
*/
    static glm::mat4 model;
    static glm::mat4 idm;
    //static FrameBuffer *m_FB;

    



    Application(const char* acWindowTitle, int iXPosition,
        int iYPosition, int iWidth, int iHeight);

public:


    std::queue<key_event> unhandled_keys;
    void handleKeys(std::string key, float time_of_event);
    void handle_input(float delta_time);
    //factory method to encapsulate application creation
    static Application* getApplication(const char* acWindowTitle, int iXPosition,
            int iYPosition, int iWidth, int iHeight);
    static Application* getApplication();

    //Due to our use case we will not 
    std::list<std::string> keysPressed;
    void addKeyPressed(std::string key);
    void removeKeyPressed(std::string key);
    void populateGamePadMap();

    void populateAxesVector();





    AssetManager* getAssetManager();
    ~Application();
    //a bunch of static methods to keep the code contained
    void init();
    void specifyContext();
    void passCallbacks();
    void createWindow();
    void loadGL();

    Camera* getEditorCamera() { return camera; };


    void allocateModules();
    void deallocateModules();

    int terminate();

    //ENTRY POINT OF THE APPLICATION
    int Main (int iQuantity, char** apcArgument);
    
    
    
    int processInput(float deltaTime);
    void showMainMenu();
    void disableCursor();
    void enableCursor();
    //callbacks
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void character_callback(GLFWwindow* window, unsigned int codepoint);
    static void cursor_enter_callback(GLFWwindow* window, int entered);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void drop_callback(GLFWwindow* window, int count, const char** paths);

    static void joystickCallback(int jid, int event);

    //A utility function
    static std::string utf8chr(int cp);
    void EditTransform(float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition);

    void renderDock();
    void resizeViewport(int width, int height);
    void getIMode();
    void loopEnd();
    void loopContent();



    void registerActions();

};
#endif
