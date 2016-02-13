#pragma once 

#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <string>


std::string RandomHexString();
std::string RandomHexString(size_t size);


