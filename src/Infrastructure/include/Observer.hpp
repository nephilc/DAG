#ifndef OBSERVER_HPP
#define OBSERVER_HPP
#include<string>

class Subject;
class Observer
{
private:
    /* data */
public:
    Observer(/* args */);
    virtual void update(std::string line);
    virtual void update(Subject *subject)=0;

    ~Observer();
};

#include<Subject.hpp>
#endif