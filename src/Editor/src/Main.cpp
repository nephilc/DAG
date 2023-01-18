#include<Application.hpp>
#include<glbe.hpp>




int Application::Main (int iQuantity, char** apcArgument)
{
    editorUI->test();
    glbe::getBackend()->displayTest();
    m_dTime = glfwGetTimerValue();
    glEnable(GL_DEPTH_TEST);
    assetManager->loadShader("shaderPrograms/animation.vs", "shaderPrograms/1.model_loading.fs", "ourShader1");
    assetManager->loadShader("shaderPrograms/1.model_loading.vs", "shaderPrograms/1.model_loading.fs", "ourShader2");

    Shader* ourShader1 = assetManager->getShaders()[0];
    assetManager->loadModel("3dmodels/arissa1/arissa1.dae", "arissa");
    
    Node* node0 =  new Node();
    Node* node1 =  new Node();
    Node* node2 =  new Node();
    node0->attachChild(node1);//should do everything
    node0->attachChild(node2);//should do everything

    assetManager->scene = node0;
    

    Animation danceAnimation ("3dmodels/Dying/Dying.dae", assetManager->getModel("arissa"));
    Animator* animator  = new Animator(&danceAnimation);
    AnimatedNode* aniNode = new AnimatedNode(assetManager->getModel("arissa"), ourShader1, animator, danceAnimation);
    node1->attachChild(aniNode);
    glEnable(GL_DEPTH_TEST);    

    while (!glfwWindowShouldClose(m_window))
    {

        glClearColor(1.0f, 1.0f, 0.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

        //PLOGD<<"starting redner1";
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput();

        //PLOGD<<"starting render";
        
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)m_iWidth / (float)m_iHeight, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();

        node0->projection = projection;

        //ImGui::Render();
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
           node0->Draw(camera, deltaTime);

        
        //Application::editorUI->render();

        //ImGui::Render();
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
//    glDeleteVertexArrays(1, &application->quadVAO);
//    glDeleteBuffers(1, &application->quadVBO);

    return 0;
}
