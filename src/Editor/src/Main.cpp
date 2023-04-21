#include<Application.hpp>
#include<glbe.hpp>
#include<WorldNode.hpp>
#include<ScreenCanvas.hpp>
#include<CameraAction.hpp>


int Application::Main (int iQuantity, char** apcArgument)
{
        
    editorUI->test();
    glbe::getBackend()->displayTest();
    assetManager->CreateDefaults();

    m_dTime = glfwGetTimerValue();
    //glEnable(GL_DEPTH_TEST);

    assetManager->registerAction(new CameraAction());
    WorldNode *worldNode = new WorldNode(1.0, 1.0, 1.0, 1.0);    
    //worldNode->SetName("WORLD NODE");
    Node* node0 =  new Node();
    Node* node1 =  new Node();
    Node* node2 =  new Node();
    worldNode->attachChild(node0);
    node0->attachChild(node1);//should do everything
    node0->attachChild(node2);//should do everything

    assetManager->scene = worldNode;
    assetManager->createScreenCanvas(1300, 800, "sc1");
    //ScreenCanvas sc();

    //node1->attachChild(aniNode);
    node1->attachChild(assetManager->defaultaniNode);    
    //glEnable(GL_DEPTH_TEST);
    //Shader frameshader("shaderPrograms/framebuffer.vs", "shaderPrograms/framebuffer.fs");
 
    //frameshader.use();
    //frameshader.setInt("screenTexture", 0);
    //populateScanCodeMap();

    

    while (!glfwWindowShouldClose(m_window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput();

        //m_FB is where you draw the nodes
        //there is also the default frame buffer
        //application->m_FB->use();
        assetManager->getScreenCanvas("sc1")->draw(currentFrame, deltaTime);
        //the viewport needs to be the same size as the framebuffer, thats it
        //the camera on the other hand has to do with the way the user view something, the window
        //we use the frame width, which is why we get the impression that the image is not stretched or  compressed
        //glViewport(0, 0, assetManager->getMainBuffer()->getWidth(), assetManager->getMainBuffer()->getHeight());
        assetManager->getMainBuffer()->use();
        //glEnable(GL_DEPTH_TEST);
        //PLOGD<<"starting redner1";

        //PLOGD<<"starting render";
        
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)m_iFrameWidth / (float)m_iFrameHeight, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();
        /*
        node0->projection = projection;

        node0->Draw(camera, deltaTime);
        */
        worldNode->projection = projection;
//###############################################insert a call to gl viewport here
        //glViewport(0, 0, assetManager->getMainBuffer()->getWidth(), assetManager->getMainBuffer()->getHeight());
        worldNode->Draw(camera, deltaTime);
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
        //glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        glEnable(GL_DEPTH_TEST);    
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        Application::editorUI->render();
        //i_fram... is used by the camera not the framebuffer
        editorUI->sceneView(0, &application->m_iFrameWidth, &application->m_iFrameHeight, &view[0][0], &projection[0][0], &application->idm[0][0], &application->model[0][0]);
        bool open = true;


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //ImGui::UpdatePlatformWindows();
        //ImGui::RenderPlatformWindowsDefault();
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();

              //  PLOGE<<"about to handle detachements";

        //assetManager->scene->handleDetachements();
            //PLOGE<<"MAIN AFTER HANDLING ALL DETACHS";


    }
    /*
    glDeleteVertexArrays(1, &application->quadVAO);
    glDeleteBuffers(1, &application->quadVBO);
*/
    return 0;
}
