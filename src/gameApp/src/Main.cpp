#include<Application.hpp>
#include<glbe.hpp>
#include<WorldNode.hpp>
#include<ScreenCanvas.hpp>
#include<NDCsquare.hpp>


#include <ft2build.h>
#include FT_FREETYPE_H


#include<Font.hpp>


//if you have many instances of a certain type that need to be edited, there will be the notion of the current object, and ops associated with it.
//app cpu usage may depend on a number of factors.
//sometimes one gets some, relative spikes in cpu usage, like 2% more, on certaain events, then it goes back to orbit around  a stable value.




int Application::Main (int iQuantity, char** apcArgument)
{
        
    glbe::getBackend()->displayTest();
    assetManager->CreateDefaults();

    m_dTime = glfwGetTimerValue();
    //glEnable(GL_DEPTH_TEST);
    registerActions();
    //after registering all actions
    assetManager->loadAllKeyMaps();


    WorldNode *worldNode = new WorldNode(1.0, 0.0, 0.0, 1.0);
    //worldNode->SetName("WORLD NODE");
    Node* node0 =  new Node();
    Node* node1 =  new Node();
    Node* node2 =  new Node();
    worldNode->attachChild(node0);
    node0->attachChild(node1);//should do everything
    node0->attachChild(node2);//should do everything

    assetManager->setCurrentScene(worldNode);
    assetManager->addScene(worldNode);

    assetManager->loadScene(assetManager->basePath + "/" + "v1/scenes/win8.xdg");

    assetManager->setCurrentScene(assetManager->getScenes()[1]);

    Shader* screenShader = assetManager->loadShader("shaderPrograms/framebuffer.vs", "shaderPrograms/framebuffer.fs");
    //ScreenCanvas sc();

    //node1->attachChild(aniNode);
    //node1->attachChild(assetManager->defaultaniNode); 
    //assetManager->defaultaniNode->play();
    //glEnable(GL_DEPTH_TEST);
    //Shader frameshader("shaderPrograms/framebuffer.vs", "shaderPrograms/framebuffer.fs");
 
    //frameshader.use();
    //frameshader.setInt("screenTexture", 0);
    //populateScanCodeMap();
    

    NDCsquare* ndcSquare = new NDCsquare();
    //just to set up the viwport of the main buffer correctly, pre resize
    glfwGetWindowSize(m_window,&m_iWidth, &m_iHeight);
    

    Font font("Arial.ttf");
    Font font2("Debrosee-ALPnL.ttf");

    while (!glfwWindowShouldClose(m_window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(deltaTime);
        if (imode == SIMULATION) {//i can move this to the process input function
            for (string& key : keysPressed)
            {
                if(getAssetManager()->currentKeyboardKeyMap!=nullptr && inputDevice==KEYBOARD_MOUSE)
                getAssetManager()->currentKeyboardKeyMap->get(key)->KeyAction(deltaTime);
                else if (getAssetManager()->currentGamepadKeyMap !=nullptr)
                {
                    //getAssetManager()->currentGamePadKeyMap->get(key)->KeyAction(deltaTime);//doing it directly in process input should be faster
                }
            }
        }
        //m_FB is where you draw the nodes
        //there is also the default frame buffer
        //application->m_FB->use();
        //the viewport needs to be the same size as the framebuffer, thats it
        //the camera on the other hand has to do with the way the user view something, the window
        //we use the frame width, which is why we get the impression that the image is not stretched or  compressed
        //glViewport(0, 0, assetManager->getMainBuffer()->getWidth(), assetManager->getMainBuffer()->getHeight());
        assetManager->getMainBuffer()->use();
        //ye^this was missing
        glViewport(0, 0, (float)assetManager->getMainBuffer()->getWidth(), (float)assetManager->getMainBuffer()->getHeight());

        //glEnable(GL_DEPTH_TEST);
        //PLOGD<<"starting redner1";

        //PLOGD<<"starting render";
        
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)assetManager->getMainBuffer()->getWidth() / (float)assetManager->getMainBuffer()->getHeight(), 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();
        /*
        node0->projection = projection;

        node0->Draw(camera, deltaTime);
        */
        assetManager->getCurrentScene()->projection = projection;
//###############################################insert a call to gl viewport here
        //glViewport(0, 0, assetManager->getMainBuffer()->getWidth(), assetManager->getMainBuffer()->getHeight());
        assetManager->getCurrentScene()->Draw(camera, deltaTime);
        font.RenderText("Health: 100", -1.0f, 0.9f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        font2.RenderText("DAGGER Engine", 0.0f, -0.9f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
        //well the y seem to render fine, but the x seem to be distoreted
        PLOGD << (float)assetManager->getMainBuffer()->getWidth();
        //handle_input(deltaTime);

        glBindFramebuffer(GL_FRAMEBUFFER, 0); 
        glViewport(0,0, m_iWidth, m_iHeight);
        // back to default
        //glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        glEnable(GL_DEPTH_TEST);    
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //i_fram... is used by the camera not the framebuffer
       

        //#######################################################################well i can just decide what buffer to draw on this square
        ndcSquare->draw(assetManager->getMainBuffer()->GetID());

        
        glfwSwapBuffers(m_window);
        glfwPollEvents();

             

    }
    /*
    glDeleteVertexArrays(1, &application->quadVAO);
    glDeleteBuffers(1, &application->quadVBO);
*/
    return 0;
}
