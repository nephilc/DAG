#include<iostream>
#include<CLIApplication.hpp>

CLIApplication::CLIApplication(/* args */)
{
    std::cout<<"STARTING CLI APPLICATION"<<std::endl;
    inputStream = new IStream();
    REPLApp = new REPLApplication(inputStream);

    inputStream->attach(REPLApp);
}

int CLIApplication::start()
{
    inputStream->listen();
    return 0;
}

CLIApplication::~CLIApplication()
{
}