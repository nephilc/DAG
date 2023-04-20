#include<Action.hpp>


IMPLEMENT_RTTI(Action, Object)

Action::Action() {
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
}

//No action 
void Action::KeyboardAction() {

}
//No Action
void Action::MouseAction(float xposIn, float yposIn, float xoffset, float yoffset) {


}
