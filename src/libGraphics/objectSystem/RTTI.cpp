#include "RTTI.hpp"
#include <plog/Log.h>
#include<iostream>

//std::vector<Rtti*> Rtti::typeList;
//----------------------------------------------------------------------------
Rtti::Rtti (std::string name, const Rtti* pkBaseType): m_name(name), m_pkBaseType(pkBaseType)
{
            //std::cout<<"rtti const"<<typeList.size()<<std::endl;

    typeList.push_back(this);
    PLOGE<<"pushing back";

}
//----------------------------------------------------------------------------
Rtti::~Rtti ()
{
}
//----------------------------------------------------------------------------
bool Rtti::IsDerived (const Rtti& rkType) const
{
        //std::cout<<"is derived";

    const Rtti* pkSearch = this;
    while (pkSearch)
    {
        if (pkSearch == &rkType)
        {
            return true;
        }
        pkSearch = pkSearch->m_pkBaseType;
    }
    return false;
}
//----------------------------------------------------------------------------
