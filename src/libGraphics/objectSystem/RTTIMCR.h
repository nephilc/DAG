#ifndef RTTIMCR_H
#define RTTIMCR_H

//----------------------------------------------------------------------------
#define DECLARE_RTTI \
public: \
    static const Rtti TYPE; \
    virtual const Rtti& GetType () const { return TYPE; }
//----------------------------------------------------------------------------
#define IMPLEMENT_RTTI(nsname,classname,baseclassname) \
    const Rtti classname::TYPE(#classname,&baseclassname::TYPE)
//----------------------------------------------------------------------------

#endif