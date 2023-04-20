#ifndef ACTION_HPP
#define ACTION_HPP
#include<Object.hpp>

enum ActionType {
	KEY,
	CURSORPOSITION
};
//keyboard actions and mouse actions are not interchangeable
//bu one could implement the same action as a key action and a cursor action in the same class
class Action : public Object
{
	DECLARE_RTTI
public:
	Action();
	~Action();
	ActionType m_at;
	//this method doesnt need to know the key to execute this action
	virtual void KeyboardAction();
	virtual void MouseAction(float xposIn, float yposIn, float xoffset, float yoffset);
private:

};





#endif // !ACTION_HPP
