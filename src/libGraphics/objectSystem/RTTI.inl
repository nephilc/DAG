//----------------------------------------------------------------------------
inline const char* Rtti::GetName () const
{
    return m_acName;
}
//----------------------------------------------------------------------------
inline int Rtti::GetDiskUsed () const
{
    // The name will be written to disk as a String object.
    int iLength = (int)strlen(m_acName);
    return sizeof(iLength) + iLength*sizeof(char);
}
//----------------------------------------------------------------------------
inline bool Rtti::IsExactly (const Rtti& rkType) const
{
    return &rkType == this;
}
//----------------------------------------------------------------------------