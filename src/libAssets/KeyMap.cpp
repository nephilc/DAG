#include<KeyMap.hpp>


IMPLEMENT_RTTI(KeyMap, Object)

KeyMap::KeyMap(KeyMapType type):m_at(type) {
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
}

KeyMap::KeyMap(std::string name, KeyMapType type):m_at(type) {
    SetName(name);//had to do it here
}
KeyMap::~KeyMap() 
{
}

bool KeyMap::set(std::string key, Action *action)
{
    
    internalKeyMap[key] = action;

    return true;
}

Action *KeyMap::get(std::string key)
{
    if(internalKeyMap.find(key) == internalKeyMap.end())
    return Action::NoAction;
    return internalKeyMap.at(key);
}

std::unordered_map<std::string, Action *> &KeyMap::getMap()
{
    // TODO: insert return statement here
    return internalKeyMap;
}

//persistance
void KeyMap::load(Stream& stream)
{
    //identify actionns by their names, there are multiple  action vectors in the AssetManager class
}
void KeyMap::save(Stream& stream)
{

}
