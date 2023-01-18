#include<CommandFunctions.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

/*
void externalHelp(vector<string> cmds, map<string, void(*)(vector<string>)> &commands)
{
    cout << "Available commands:" << endl;
    for (auto& [command, func] : commands) {
        cout << " - " << command << endl;
    }
}
*/
// Function to handle the "echo" command
void echo(vector<string> args) {
    // Concatenate all arguments with spaces
    stringstream ss;
    for (auto& arg : args) {
        ss << arg << " ";
    }
    // Print the concatenated string
    cout << ss.str() << endl;
}

// Function to handle the "add" command
void add(vector<string> args) {
    if (args.size() < 2) {
        cout << "Usage: add <number> <number> ..." << endl;
        return;
    }

    int sum = 0;
    for (auto& arg : args) {
        // Attempt to convert the argument to an integer
        try {
            sum += stoi(arg);
        } catch (invalid_argument& e) {
            cout << "Invalid argument: " << arg << endl;
            return;
        }
    }
    cout << "The sum is: " << sum << endl;
}

// Function to handle the "exit" command
void exit(vector<string> args) {
    cout << "Exiting..." << endl;
    exit(0);
}

