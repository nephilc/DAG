#include<Action.hpp>


//IMPLEMENT_RTTI(Action, Object)
Action *Action::NoAction = new Action("No Action");

Action::Action() {
    SetName("SOME ACTION" + std::to_string(GetID()));//had to do it here
}

Action::Action(std::string name) {
    SetName(name);//had to do it here
}
Action::~Action() {
}

//No action 
void Action::KeyAction(float dt) {

}
//No Action
void Action::MouseAction(float xposIn, float yposIn, float xoffset, float yoffset) {


}
//No action
void Action::GamePadAction()
{
}
void Action::AxesAction2D(float xVal, float yVal)
{
}
void Action::AxesAction1D(float val)
{
}