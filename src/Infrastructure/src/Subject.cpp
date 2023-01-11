#include<iostream>
#include<Subject.hpp>
/// @brief sdfsdfsdfdsf

Subject::Subject(/* args */)
{
}

void Subject::attach(Observer *observer)
{
    observers.push_back(observer);
}

void Subject::notify()
{
    for(Observer * obs: observers)
    {
        obs->update(this);
    }
}

Subject::~Subject()
{
}