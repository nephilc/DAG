
#include "backend.hpp"

const char* DrawModeStrings[8] = {
    "MD_POINTS",
    "MD_LINES",
    "MD_TRI"
};

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
