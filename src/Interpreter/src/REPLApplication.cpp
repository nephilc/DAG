#include<iostream>
#include<REPLApplication.hpp>
#include <stdlib.h>

REPLApplication::REPLApplication(IStream *p_inputStream): inputStream(p_inputStream)
{
}

void REPLApplication::read()
{
}

void REPLApplication::evaluate()
{
}

void REPLApplication::print()
{
}

void REPLApplication::update(Subject *subject)
{
    std::cout<<"REPL UPDATED"<<std::endl;
    std::string inputState = inputStream->getInputState();
        // Evaluate the input
    if (inputState == "exit") {
      exit(0);
    } else if (inputState == "hello") {
      std::cout << "Hello, world!" << std::endl;
    } else {
      std::cout << "Unknown command" << std::endl;
    }

}

void REPLApplication::programCyle()
{
}

REPLApplication::~REPLApplication()
{
}