#ifndef STREAM_HPP
#define STREAM_HPP
#include<string>
#include <iostream>
#include <fstream>

class Object;
class Stream
{
public:

	std::fstream myfile;
	Stream(std::string fileName);
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

	void read(const std::string& str);
	void read(int iQuantity, const float* afValue);//important for saving transforms, or any kind of array


	// read/write always applied to buffer in memory
	int m_iBufferSize, m_iBufferNext;
	char* m_acBuffer;


private:

};

#include<Object.hpp>
#endif // !Stream
