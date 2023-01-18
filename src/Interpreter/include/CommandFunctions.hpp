#ifndef COMMANDFUCNTIONS_HPP
#define COMMANDFUNCTIONS_HPP

#include <string>
#include <vector>

using namespace std;


//void externalHelp(vector<string> args,  map<string, void(*)(vector<string>)> &commands);
void echo(vector<string> args);
void add(vector<string> args);
void exit(vector<string> args);
void displayApplicationContext(vector<string> args);




#endif
