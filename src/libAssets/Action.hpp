#ifndef ACTION_HPP
#define ACTION_HPP
#include<Object.hpp>

enum ActionType {
	KEY,
	MOUSE,
	ALL
};
//keyboard actions and mouse actions are not interchangeable
//bu one could implement the same action as a key action and a cursor action in the same class
class Action : public Object
{
	DECLARE_RTTI
public:
	Action();
	Action(std::string name);
	~Action();
	ActionType m_at;
	//this method doesnt need to know the key to execute this action
	virtual void KeyAction(float dt=0);
	virtual void MouseAction(float xposIn, float yposIn, float xoffset, float yoffset);
	virtual void GamePadAction();

private:

};





#endif // !ACTION_HPP
