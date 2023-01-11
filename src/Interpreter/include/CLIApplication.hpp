#ifndef CLIApplication_HPP
#define CLIApplication_HPP
#include<Observer.hpp>
#include<IStream.hpp>
#include<REPLApplication.hpp>
class CLIApplication
{    
private:
//CREATE REPL APP
//CREATE CONSOLE INPUT STREAM, WATCH THE CIS
IStream *inputStream;
REPLApplication *REPLApp;
public:
    CLIApplication(/* args */);
    int start();
    //maybe i wont need this one, everytime the class is updated we execute a loop
    ~CLIApplication();
};



#endif
