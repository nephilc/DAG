#ifndef OBJECT_HPP
#define OBJECT_HPP

#include<vector>
#include<string>
class Object
{
private:
    /* data */
public:
    Object(/* args */);
    ~Object();

    void SetName (const std::string& rkName);
    const std::string& GetName () const;
    unsigned int GetID () const;
    static unsigned int GetNextID ();
private:
    std::string m_kName;
    unsigned int m_uiID;
    static unsigned int ms_uiNextID;

};





#endif
