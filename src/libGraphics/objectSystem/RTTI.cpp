#include "RTTI.hpp"


std::vector<Rtti*> Rtti::typeList;
//----------------------------------------------------------------------------
Rtti::Rtti (std::string name, const Rtti* pkBaseType): m_name(name), m_pkBaseType(pkBaseType)
{
    typeList.push_back(this);
}
//----------------------------------------------------------------------------
Rtti::~Rtti ()
{
}
//----------------------------------------------------------------------------
bool Rtti::IsDerived (const Rtti& rkType) const
{
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
