//----------------------------------------------------------------------------
// run-time type information
//----------------------------------------------------------------------------
const Rtti& Object::GetType () const
{
    return TYPE;
}

//----------------------------------------------------------------------------
bool Object::IsExactly (const Rtti& rkType) const
{
    return GetType().IsExactly(rkType);
}
//----------------------------------------------------------------------------
bool Object::IsDerived (const Rtti& rkType) const
{
    return GetType().IsDerived(rkType);
}
//----------------------------------------------------------------------------
bool Object::IsExactlyTypeOf (const Object* pkObj) const
{
    return pkObj && GetType().IsExactly(pkObj->GetType());
}
//----------------------------------------------------------------------------
bool Object::IsDerivedTypeOf (const Object* pkObj) const
{
    return pkObj && GetType().IsDerived(pkObj->GetType());
}
//----------------------------------------------------------------------------


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


//----------------------------------------------------------------------------
// smart pointers
//----------------------------------------------------------------------------
void Object::IncrementReferences ()
{
    m_iReferences++;
}
//----------------------------------------------------------------------------
int Object::GetReferences () const
{
    return m_iReferences;
}
//----------------------------------------------------------------------------
