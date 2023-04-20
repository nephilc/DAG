#include<iostream>
using namespace std;
#include <plog/Log.h> 
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Appenders/ColorConsoleAppender.h"

#include <Application.hpp>

//can register the action s here
#include<AssetManager.hpp>
#include<Action.hpp>


void atexitWork();

Application *application= 0;

//make this virtual part of application
int main(int argc, char** argv)
{
	atexit(atexitWork);
	std::cout<<"EDITOR APPLICATION"<<std::endl;
	cout<<"ASSET TEST"<<endl;
	#ifndef PLOG_DISABLE_LOGGING
	static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, &consoleAppender);
    #endif
	const char *title = "this is the title";
	application=  Application::getApplication("editor application", 0, 0, 600 , 800);
	application->Main(argc, argv);
	delete application;


	
	return 0;
}

void atexitWork()
{
	printf("EXITING APPLICATION\n");
}
