#include<KeyMap.hpp>
#include<Vector>
#include<sstream>
#include <AssetManager.hpp>


IMPLEMENT_RTTI(KeyMap, Object)



std::vector<std::string> splitMapping(const std::string& line)
{
    std::vector<std::string> mapping;
    std::string relativePath;
    std::string part;
    std::stringstream ss(line);
    while (std::getline(ss, part, '>')) {
        mapping.push_back(part);
    }
    return mapping;

}



KeyMap::KeyMap() {

}



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
    Object::load(stream);
    m_at = (KeyMapType)stoi(stream.readln());
    int KMSize = stoi(stream.readln());
    for (int i = 0; i < KMSize; ++i)
    {
    std::string mapping = stream.readln();
    std::vector<std::string> parts = splitMapping(mapping);
    if(m_at==KEYBOARD_MAP)
    internalKeyMap[parts[0]] = AssetManager::getInstance()->getKeyAction(parts[1]);
    if(m_at==MOUSE_MAP)
        internalKeyMap[parts[0]] = AssetManager::getInstance()->getMouseAction(parts[1]);

    }

    //identify actionns by their names, there are multiple  action vectors in the AssetManager class
}
void KeyMap::save(Stream& stream)
{
    Object::save(stream);
    stream.writeln(m_at);
    stream.writeln(internalKeyMap.size());
    for (auto i = internalKeyMap.begin(); i != internalKeyMap.end(); ++i) 
    {
        stream.writeln(i->first + std::string(">")+i->second->GetName());

    }

}
