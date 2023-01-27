#include "EditorUI.hpp"
#define DECLARE_FACTORY(classname)\
    void classname##_##factory(Node *parent)\
    { parent->attachChild(new classname());}

#define FACTORY(classname) classname##_##factory(Node *parent)





void EditorUI::init_RTTI()
{

}

DECLARE_FACTORY(Node) 

//DECLARE_FACTORY(AnimatedNode)

