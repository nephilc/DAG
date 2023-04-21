#include<Action.hpp>


IMPLEMENT_RTTI(Action, Object)

Action::Action() {
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
}

Action::Action(std::string name) {
    SetName(name);//had to do it here
}
Action::~Action() {
}

//No action 
void Action::KeyAction() {

}
//No Action
void Action::MouseAction(float xposIn, float yposIn, float xoffset, float yoffset) {


}
//No action
void Action::GamePadAction()
{
}
