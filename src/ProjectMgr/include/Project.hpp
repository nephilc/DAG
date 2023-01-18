#ifndef PROJECT_HPP
#define PROJECT_HPP
#include<string>

using namespace std;
class Project
{
private:
    
    string projectName;
    string projectPath;
    //add creaton date

        
public:
    Project(string path, string name);
    void save();
    void load();
    ~Project();
};

#endif