#ifndef STREAM_HPP
#define STREAM_HPP

class Object;
class Stream
{
public:
	Stream();
	~Stream();
	//A link class, or otherwise

	void load(Object* object);
	void save(Object* object);


	//write functions for any kind of write operation that we would like to perform
	void write(const Object* object);
	void write(const std::string& str);
	void write(int iQuantity, const float* afValue);//important for saving transforms, or any kind of array


	// read/write always applied to buffer in memory
	int m_iBufferSize, m_iBufferNext;
	char* m_acBuffer;


private:

};

#include<Object.hpp>
#endif // !Stream
