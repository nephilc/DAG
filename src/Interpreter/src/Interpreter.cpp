#include<iostream>
#include<Interpreter.hpp>
#include<CommandFunctions.hpp>
/// @brief sdfsdfsdfdsf


using namespace std;
Interpreter::Interpreter(/* args */)
{
// Populate the map with commands and their corresponding functions
    //commands["help"] = help;
    commands["echo"] = echo;
    commands["add"] = add;
    commands["exit"] = exit;

}

Interpreter::~Interpreter()
{
}
// Function to handle the "help" command
void Interpreter::help() 
{
    cout << "Available commands:" << endl;
    for (auto& [command, func] : commands) {
        cout << " - " << command << endl;
    }

}

void Interpreter::interpret(string input)
{

        stringstream ss(input);
        string command;
        ss >> command;

        if (commands.count(command) == 0) {
        	if(command == "help")
        	{
        	help();
        	}
        	else
            cout << "Invalid command. Type 'help' for a list of commands." << endl;
            
        } else {
            vector<string> args;
            string arg;
            // Store all the remaining tokens in the vector<string>
            while (ss >> arg) {
                args.push_back(arg);
            }
            // Call the function associated with the entered command
            commands[command](args);
        }}
