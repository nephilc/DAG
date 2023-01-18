#ifndef Interpreter_HPP
#define Interpreter_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <CommandFunctions.hpp>
using namespace std;



class Interpreter
{
private:
map<string, void(*)(vector<string>)> commands;

public:
    Interpreter(/* args */);
    ~Interpreter();
    void help();
    void interpret(string input);
};



#endif
