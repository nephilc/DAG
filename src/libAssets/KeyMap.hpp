#ifndef KEYMAP_HPP
#define KEYMAP_HPP
#include<Object.hpp>
#include<unordered_map>
#include<Action.hpp>

//when opening a project or loading a game all keymaps should be loaded.
//all keymaps should be put in the same common directory.
//a db file would be under the common\KM directory to contain a list of all KeyMaps. That file would be "db.kmf".

enum KeyMapType {
	KEYBOARD_MAP=0,
    MOUSE_MAP,
	GAMEPAD_MAP,
	AXES_MAP
};

//keyboard KeyMaps and mouse KeyMaps are not interchangeable
//bu one could implement the same KeyMap as a key KeyMap and a cursor KeyMap in the same class
class KeyMap : public Object
{
	DECLARE_RTTI
public:

	KeyMapType m_at;//persist
	std::unordered_map<std::string, Action*> internalKeyMap;//persist
	std::string fileName;


	KeyMap(KeyMapType type);
	KeyMap();
	KeyMap(std::string name, KeyMapType type);
	~KeyMap();
	 bool set(std::string key, Action *action);
    Action* get(std::string key);
     std::unordered_map<std::string, Action*>& getMap();
	 //persistance
	 void load(Stream& stream);
	 void save(Stream& stream);
	 std::string getFileName() { return fileName; };
	 void setFileName(std::string newName) { this->fileName = newName; };
private:

};





#endif // !KEYMAP_HPP
