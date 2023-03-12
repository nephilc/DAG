//----------------------------------------------------------------------------
inline std::string Rtti::GetName () const
{
    return m_name;
}
/*
//----------------------------------------------------------------------------
inline int Rtti::GetDiskUsed () const
{
    // The name will be written to disk as a String object.
    int iLength = (int)strlen(m_acName);
    return sizeof(iLength) + iLength*sizeof(char);
}
*/
#include<iostream>
//----------------------------------------------------------------------------
inline bool Rtti::IsExactly (const Rtti& rkType) const
{
    std::cout<<"rtti const"<<typeList.size()<<std::endl;

    return &rkType == this;
}
//----------------------------------------------------------------------------
