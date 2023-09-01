#ifndef CAMERAACTION_HPP
#define CAMERAACTION_HPP
#include<Action.hpp>
#include<Application.hpp>//the assetManager could be a signleton, so that i could access it directly
#include<Camera.hpp>


/*
action files may be header only, for increased productivity purposes.
The reason for this is that the number of action files may become relativlty high.

*/


class CameraAction : public Action
{
	DECLARE_RTTI

public:
	CameraAction() {
		SetName("CAMERA ACTION");
		Action::m_at = ALL;
		camera = Application::getApplication()->getEditorCamera();
	};

	~CameraAction() {
	};

	void KeyAction(float dt) override {
	};
	void MouseAction(float xposIn, float yposIn, float xoffset, float yoffset) override {
		camera->ProcessMouseMovement(xoffset, yoffset);


	};
	void GamePadAction() override {
	};

private:
	Camera* camera;
};


IMPLEMENT_RTTI(CameraAction, Action)


#endif // !CAMERAACTION_HPP
