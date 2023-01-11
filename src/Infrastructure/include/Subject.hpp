#ifndef SUBJECT_HPP
#define SUBJECT_HPP
#include<Observer.hpp>
#include<vector>
class Subject
{
private:
    /* data */
    std::vector<Observer*> observers;
public:
    Subject(/* args */);
    void attach(Observer* observer);
    void notify();
    ~Subject();
};

#endif