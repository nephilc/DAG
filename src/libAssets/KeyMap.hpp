#ifndef KEYMAP_HPP
#define KEYMAP_HPP
#include<Object.hpp>
#include<unordered_map>
#include<Action.hpp>


enum KeyMapType {
	KEYBOARD_MAP,
    MOUSE_MAP,
	GAMEPAD_MAP
};

//keyboard KeyMaps and mouse KeyMaps are not interchangeable
//bu one could implement the same KeyMap as a key KeyMap and a cursor KeyMap in the same class
class KeyMap : public Object
{
	DECLARE_RTTI
public:
	KeyMap(KeyMapType type);
	KeyMap(std::string name, KeyMapType type);
	~KeyMap();
	KeyMapType m_at;
    std::unordered_map<std::string, Action*> internalKeyMap;
    bool set(std::string key, Action *action);
    Action* get(std::string key);
     std::unordered_map<std::string, Action*>& getMap();
	
private:

};





#endif // !KEYMAP_HPP
