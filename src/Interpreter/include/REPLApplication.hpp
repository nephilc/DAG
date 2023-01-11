#ifndef REPLApplication_HPP
#define REPLApplication_HPP
#include<Observer.hpp>
#include<IStream.hpp>
class REPLApplication : public Observer
{
    
private:
//add io handler
IStream *inputStream;
public:
    REPLApplication(IStream *p_inputStream);
    void read();
    void evaluate();
    void print();
    void update(Subject *subject);
    //maybe i wont need this one, everytime the class is updated we execute a loop
    virtual void programCyle();
    ~REPLApplication();
};



#endif