#ifndef ISTREAM_HPP
#define ISTREAM_HPP
#include<string>
#include<Subject.hpp>
//make this one abstract, could also be singleton
class IStream : public Subject
{
private:
    std::string inputState;
public:
    IStream(/* args */);
    void listen();
    std::string getInputState();
    ~IStream();
};
#endif