#include<Stream.hpp>
#include <plog/Log.h> 



Stream::Stream(std::string fileName)
{
	myfile.open(fileName, std::ios::out);

	if (myfile.is_open()) 
	{
		PLOGE << "COULDN'T OPEN FILE";
	}
	else
	{
		PLOGI << "file opened " << fileName;
	}
}

Stream::~Stream()
{
	myfile.close();

}
//read with getline into a sstring 
//write using the << operator

void Stream::writeln(const std::string& str)
{
	PLOGI << "Writting" << str;
	myfile << str << "\n";

}
void Stream::write(const std::string& str)
{
	PLOGI << "Writting" << str;

}

void Stream::writeln(int iQuantity, const float* afValue) 
{
	
	for (int i = 0; i < iQuantity; ++i)
	{
		myfile << afValue[i] << " ";
	}
	myfile << "\n";
}

void Stream::write(void* ptr)
{
	myfile << ptr<< " ";

}

