#include<iostream>
#include<CLIApplication.hpp>
#include<Project.hpp>
//make this virtual part of application
void atexitWork();
CLIApplication *app = 0;
int main(int argc, char** argv)
{
	atexit(atexitWork);

	
	std::cout<<"REPL APPLICATION"<<std::endl;
	Project *project = new Project("/home/radon/Documents/RenderingProj", "RedneringProj");
	app = new CLIApplication();
	app->start();
	return 0;
}

void atexitWork()
{
	printf("EXITING APPLICATION\n");
	delete app;

}
