#include<Application.hpp>

#include<CameraAction.hpp>
#include<CameraActionUp.hpp>
#include<CameraActionDown.hpp>

#include<CameraActionLeft.hpp>

#include<CameraActionRight.hpp>
#include<CameraActionForward.hpp>
#include<CameraActionBackwards.hpp>
#include<CameraActionLook.hpp>


void Application::registerActions() 
{

    assetManager->registerAction(new CameraAction());
    assetManager->registerAction(new CameraActionUP());
    assetManager->registerAction(new CameraActionDown());
    assetManager->registerAction(new CameraActionLeft());
    
    assetManager->registerAction(new CameraActionRight());
    assetManager->registerAction(new CameraActionForward());
    assetManager->registerAction(new CameraActionBackwards());
    assetManager->registerAction(new CameraActionLook());
    

}