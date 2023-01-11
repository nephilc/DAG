#ifndef CIS_HPP
#define CIS_HPP
#include<string>
#include<IStream.hpp>
//make this one a signleton
class CIS : public IStream
{
private:
    std::string inputState;
public:
    CIS(/* args */);
    ~CIS();
};

#endif