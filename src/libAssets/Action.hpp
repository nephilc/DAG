#ifndef ACTION_HPP
#define ACTION_HPP
#include<Object.hpp>
//the object name of an action has to be set programmatically, it shouldnt include the id so that it remains constant, it will be used to reference the action.
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
    static  Action *NoAction;

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
