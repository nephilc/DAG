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
    //virtual const Rtti& GetType() const;
    //the role of this method is to read a line and to dispatch a factory method//not anymore
    
    //the only two methods i will use, the same way i saved the scene. These will be the only two methods i will use.
    virtual void load(Stream& stream);
    virtual void save(Stream& stream);


    static Object* objectFactoryMethod(Stream& stream);



private:
    static std::map<std::string, FactoryMethod> factoryMethodMap;
    std::string m_kName;
    unsigned int m_uiID;
    static unsigned int ms_uiNextID;

};





#endif
