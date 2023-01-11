#include<iostream>
#include<CLIApplication.hpp>
//make this virtual part of application
void atexitWork();
CLIApplication *app = 0;
int main(int argc, char** argv)
{
	atexit(atexitWork);
	std::cout<<"REPL APPLICATION"<<std::endl;
	app = new CLIApplication();
	app->start();
	return 0;
}

void atexitWork()
{
	printf("EXITING APPLICATION\n");
	delete app;

}
