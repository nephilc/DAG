#include "RTTI.hpp"

//----------------------------------------------------------------------------
Rtti::Rtti (const char* acName, const Rtti* pkBaseType)
{
    m_acName = acName;
    m_pkBaseType = pkBaseType;
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