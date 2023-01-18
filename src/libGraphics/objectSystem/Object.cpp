#include "Object.hpp"

unsigned int Object::ms_uiNextID = 0;

Object::Object(/* args */)
{
    m_uiID = ms_uiNextID++;


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


