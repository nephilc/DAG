#include "Object.hpp"
#include<plog/Log.h>

const Rtti Object::TYPE("Object",0);
unsigned int Object::ms_uiNextID = 0;

//will need to initialize this vector at startup 
//std::map<std::string, Object::FactoryMethod> Object::factoryMethodMap;
/*
void objectFactoryMethod(Stream& stream)
{

}
*/

Object::Object(/* args */)
{
    m_uiID = ms_uiNextID++;
    SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here
    PLOGD<<"object const"<<TYPE.typeList.size();

}

Object::~Object()
{
}

///either i use std stream directly, instead of creating my own stream, or my stream class would be an adapter to std::stream
//no need to create a system class
/*
void Object::save(Stream& stream)//std::OStream uncomment this
{
    //stream.Write(std::string(GetType().GetName()));

    // address of object for unique ID on Load/Link
    //stream.Write((Object*)this);

    // name of object
    //stream.Write(m_kName);

}
*/





//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
void Object::SetName (const std::string& rkName)
{
    m_kName = rkName;
}
//----------------------------------------------------------------------------
const std::string& Object::GetName () const
{
    return m_kName;
}
//----------------------------------------------------------------------------
unsigned int Object::GetID () const
{
    return m_uiID;
}
//----------------------------------------------------------------------------
unsigned int Object::GetNextID ()
{
    return ms_uiNextID;
}
//----------------------------------------------------------------------------


void Object::save(Stream& stream) 
{
    //start with child type save, then move on to other save
    //object properties are loaded last when you reach the object props, you know you have loaded an entire node
    //you wouldnt need the pointers if the load and saves are done recursively
    stream.writeln(TYPE.GetName());
    stream.writeln(m_kName);
    
}


void Object::load(Stream& stream) 
{
    
    //While(stream.getline)
    //extract type
    //call factory method of that type//pass to it the stream so that it may call factory methods itself
    std::string typeName = stream.readln();
    if (typeName != TYPE.GetName()) PLOGE << "Wrong loader, Expected " << TYPE.GetName() << " found in file" << typeName;
    this->m_kName = stream.readln();

}

