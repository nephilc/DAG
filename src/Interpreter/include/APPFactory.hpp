#ifndef CLIApplication_HPP
#define CLIApplication_HPP
#include<Observer.hpp>
#include<IStream.hpp>

class CLIApplication
{
private:
//CREATE REPL APP
//CREATE CONSOLE INPUT STREAM, WATCH THE CIS

public:
    CLIApplication(/* args */);
    void read();
    void evaluate();
    void print();
    //maybe i wont need this one, everytime the class is updated we execute a loop
    virtual void programCyle();
    ~CLIApplication();
};



#endif