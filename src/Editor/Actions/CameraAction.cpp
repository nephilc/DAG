#include<CameraAction.hpp>

IMPLEMENT_RTTI(CameraAction, Action)

CameraAction::CameraAction()
{
	SetName("CAMERA ACTION " + std::to_string(GetID()));
	Action::m_at = ALL;
	camera = Application::getApplication()->getEditorCamera();
}

void CameraAction::KeyAction() {

}

void CameraAction::MouseAction(float xposIn, float yposIn, float xoffset, float yoffset) {
	camera->ProcessMouseMovement(xoffset, yoffset);


}

void CameraAction::GamePadAction() {

}



CameraAction::~CameraAction()
{
}
