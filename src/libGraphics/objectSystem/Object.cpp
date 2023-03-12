#include "Object.hpp"
#include<plog/Log.h>

const Rtti Object::TYPE("Object",0);
unsigned int Object::ms_uiNextID = 0;

Object::Object(/* args */)
{
    m_uiID = ms_uiNextID++;
SetName((this->GetType().GetName() + std::to_string(GetID())));//had to do it here

    PLOGD<<"object const"<<TYPE.typeList.size();

}

Object::~Object()
{
}






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


