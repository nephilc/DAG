#include<Application.hpp>
#include<glbe.hpp>
#include<WorldNode.hpp>



int Application::Main (int iQuantity, char** apcArgument)
{
    editorUI->test();
    glbe::getBackend()->displayTest();
    assetManager->CreateDefaults();

    m_dTime = glfwGetTimerValue();
    glEnable(GL_DEPTH_TEST);

    WorldNode *worldNode = new WorldNode(1.0, 0.0, 0.0, 1.0);    
    //worldNode->SetName("WORLD NODE");
    Node* node0 =  new Node();
    Node* node1 =  new Node();
    Node* node2 =  new Node();
    worldNode->attachChild(node0);
    node0->attachChild(node1);//should do everything
    node0->attachChild(node2);//should do everything

    assetManager->scene = worldNode;
    

    //node1->attachChild(aniNode);
    node1->attachChild(assetManager->defaultaniNode);
    
    glEnable(GL_DEPTH_TEST);
    Shader frameshader("shaderPrograms/framebuffer.vs", "shaderPrograms/framebuffer.fs");
    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
/*
    glGenVertexArrays(1, &application->quadVAO);
    glGenBuffers(1, &application->quadVBO);
    glBindVertexArray(application->quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, application->quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    frameshader.use();
    //frameshader.setInt("screenTexture", 0);
*/
    

    while (!glfwWindowShouldClose(m_window))
    {
        //m_FB is where you draw the nodes
        //there is also the default frame buffer
        application->m_FB->use();
        glEnable(GL_DEPTH_TEST);
        //PLOGD<<"starting redner1";
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput();

        //PLOGD<<"starting render";
        
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)m_iFrameWidth / (float)m_iFrameHeight, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();
        /*
        node0->projection = projection;

        node0->Draw(camera, deltaTime);
        */
        worldNode->projection = projection;

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
