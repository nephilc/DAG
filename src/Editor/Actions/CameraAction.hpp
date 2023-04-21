#ifndef CAMERAACTION_HPP
#define CAMERAACTION_HPP
#include<Action.hpp>
#include<Application.hpp>//the assetManager could be a signleton, so that i could access it directly
#include<Camera.hpp>
class CameraAction : public Action
{
	DECLARE_RTTI

public:
	CameraAction();
	~CameraAction();

	void KeyAction() override;
	void MouseAction(float xposIn, float yposIn, float xoffset, float yoffset) override;
	void GamePadAction() override;

private:
	Camera* camera;
};



#endif // !CAMERAACTION_HPP
