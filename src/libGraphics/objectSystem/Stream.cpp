#include<Stream.hpp>
#include <plog/Log.h> 



Stream::Stream(std::string fileName, Mode mode)
{
	if(mode==WRITE_MODE)
	myfile.open(fileName, std::ios::out);
	else if(mode == READ_MODE)
	{
		myfile.open(fileName, std::ios::in);

	}
	else {
		myfile.open(fileName, std::ios::trunc);

	}
	if (!myfile.is_open())
	{
		PLOGE << "COULDN'T OPEN FILE";
		PLOGE << fileName;
		openSuccess=false;
	}
	else
	{
		PLOGI << "file opened " << fileName;
		openSuccess=true;
	}
}

Stream::Stream(std::fstream file) 
{
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
void Stream::writeln(const int number)
{
	PLOGI << "Writting" << number;
	myfile << number << "\n";

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

std::string Stream::readln() 
{
	//getline, return it as str
	std::string temp;
	std::getline(myfile, temp);
	return temp;

}
//important for saving transforms, or any kind of array
void Stream::readln(int iQuantity, float* afValue) 
{
	//getline, return it as str
	std::string line;
	std::getline(myfile, line);
	std::istringstream iss(line);
	//get line split it and fill up the array in the parametres
	std::string part;
	int i = 0;
	while (i<iQuantity && std::getline(iss, part, ' ')) {
		afValue[i] = std::stof(part);
		i++;
	}
}

bool Stream::isOpen()
{
    return openSuccess;
}


bool Stream::eof()
{
	return 	myfile.eof();
}

