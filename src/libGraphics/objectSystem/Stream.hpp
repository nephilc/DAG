#ifndef STREAM_HPP
#define STREAM_HPP
#include<string>
#include <iostream>
#include <fstream>

//fstream adapter class



enum Mode {
	READ_MODE,
	WRITE_MODE
};

class Object;
class Stream
{
public:

	std::fstream myfile;
	Stream(std::string fileName,Mode mode);
	Stream(std::fstream file);
	~Stream();
	//A link class, or otherwise

	void load(Object* object);
	void save(Object* object);


	//write functions for any kind of write operation that we would like to perform
	//void write(const Object* object);
	void writeln(const std::string& str);
	void write(const std::string& str);
	void writeln(int iQuantity, const float* afValue);//important for saving transforms, or any kind of array
	void write(void* ptr);
	//void write

	std::string readln();
	void readln(int iQuantity, float* afValue);//important for saving transforms, or any kind of array
	//the speed of memcopy

	// read/write always applied to buffer in memory
	int m_iBufferSize, m_iBufferNext;

	char* m_acBuffer;

private:

};

#include<Object.hpp>
#endif // !Stream
