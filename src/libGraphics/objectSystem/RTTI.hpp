#ifndef RTTI_H
#define RTTI_H
#include <string>
#include<vector>
#include "RTTIMCR.h"

class  Rtti
{
public:
    // The name must be unique among all objects in the system.  In the Wm4
    // namespace, a class Foo should use "Wm4.Foo".  If an application has
    // another namespace, SomeName, then the name should be "SomeName.Foo".
    static std::vector<Rtti*> typeList;
    static std::vector<Rtti*> nodeList;

    Rtti (std::string name, const Rtti* pkBaseType);
    ~Rtti ();
    std::string GetName () const;
    int GetDiskUsed () const;

    bool IsExactly (const Rtti& rkType) const;
    bool IsDerived (const Rtti& rkType) const;


private:
    const std::string m_name;
    const Rtti* m_pkBaseType;
};
//extern std::vector<Rtti*> typeList;
//std::vector<Rtti*> Rtti::typeList;
#include "RTTI.inl"

#endif
