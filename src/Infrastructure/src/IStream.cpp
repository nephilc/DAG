#include<iostream>
#include<IStream.hpp>
/// @brief sdfsdfsdfdsf

IStream::IStream(/* args */)
{
}

void IStream::listen()
{
    while (true) {
    std::cout << "> ";
    std::getline(std::cin, inputState);
    notify();
  }
}

std::string IStream::getInputState()
{
  return inputState;
}

IStream::~IStream()
{
}