#pragma once 


#include <sstream>


template<class Data>
std::string Hex(const Data &data)
{
    std::stringstream stream;
    stream<<"0x"<<std::hex<<data;
    return stream.str();
}
