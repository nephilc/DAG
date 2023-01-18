
#include "backend.hpp"

backend* backend::be = 0;

backend::backend()
{}
backend::~backend()
{}

backend* backend::getBackend()
{
    //test here that the backend has been created by the client, using some concrete backend. doesn't need to know the concrete backend.
    if(be==0) std::cout<<"BACKEND HASN'T BEEN SET BY THE CLIENT. THE CLIENT HAS TO SET THE BACKEND"<<std::endl;
    return be;
}
