#ifndef CAMERAACTIONLOOK_HPP
#define CAMERAACTIONLOOK_HPP
#include<Action.hpp>
#include<Application.hpp>//the assetManager could be a signleton, so that i could access it directly
#include<Camera.hpp>


/*
action files may be header only, for increased productivity purposes.
The reason for this is that the number of action files may become relativlty high.

*/


class CameraActionLook : public Action
{
	//DECLARE_RTTI

public:
	CameraActionLook() {
		SetName("CAMERA ACTION LOOK");
		Action::m_at = ALL;
		camera = Application::getApplication()->getEditorCamera();
	};

	~CameraActionLook() {
	};

	void KeyAction(float dt) override {
	};
	void MouseAction(float xposIn, float yposIn, float xoffset, float yoffset) override {
		camera->ProcessMouseMovement(xoffset, yoffset);


	};
	void GamePadAction() override {
	};
	virtual void AxesAction2D(float xVal, float yVal) {
		camera->ProcessMouseMovement(xVal, yVal);
	}
	virtual void AxesAction1D(float val){
	}


private:
	Camera* camera;
};


//IMPLEMENT_RTTI(CameraActionLook, Action)


#endif // !CAMERAACTION_HPP
