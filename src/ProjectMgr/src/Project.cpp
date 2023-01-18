#include<Project.hpp>
#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"

Project::Project(string path, string name): projectName(name), projectPath(path)
{
        rapidjson::Document scene;
        scene.SetObject();
        scene.AddMember("name", "level1", scene.GetAllocator());
        scene.AddMember("objects", 3, scene.GetAllocator());
        
        
        
        
        
        FILE* fp = fopen((projectPath+ "/" +name).c_str(), "wb");
        char writeBuffer[65536];
        rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
        rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
        scene.Accept(writer);
        fclose(fp);
}

void Project::save()
{
}

void Project::load()
{
}

Project::~Project()
{
}
