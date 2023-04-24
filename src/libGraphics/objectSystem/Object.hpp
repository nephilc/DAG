#ifndef OBJECT_HPP
#define OBJECT_HPP

#include<vector>
#include<string>
#include<RTTI.hpp>
#include<Stream.hpp>
#include<map>

class Object
{
    DECLARE_RTTI
    typedef Object* (*FactoryMethod)(Stream&);

private:
    /* data */
public:
    Object(/* args */);
    ~Object();

    void SetName (const std::string& rkName);
    const std::string& GetName () const;
    unsigned int GetID () const;
    static unsigned int GetNextID ();

    void load(Stream& stream);
    void save(Stream& stream);



private:
    std::map<std::string, FactoryMethod> factoryMethodMap;
    std::string m_kName;
    unsigned int m_uiID;
    static unsigned int ms_uiNextID;

};





#endif
