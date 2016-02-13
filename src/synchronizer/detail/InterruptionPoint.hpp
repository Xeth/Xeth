#pragma once 

#include <stdexcept>

namespace Xeth{


class InterruptionException : public std::exception
{};


class InterruptionPoint
{
    public:
        InterruptionPoint();

};


}
