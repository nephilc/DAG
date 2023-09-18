#ifndef CAMERAACTIONLEFT_HPP
#define CAMERAACTIONLEFT_HPP
#include<Action.hpp>
#include<Application.hpp>//the assetManager could be a signleton, so that i could access it directly
#include<Camera.hpp>


/*
action files may be header only, for increased productivity purposes.
The reason for this is that the number of action files may become relativlty high.

*/


class CameraActionLeft : public Action
{
	//DECLARE_RTTI

public:
	CameraActionLeft() {
		SetName("CAMERA ACTION LEFT");
		Action::m_at = ALL;
		camera = Application::getApplication()->getEditorCamera();
	};

	~CameraActionLeft() {
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


//IMPLEMENT_RTTI(CameraActionLeft, Action)


#endif // !CAMERAACTION_HPP
