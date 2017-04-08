#pragma once 

#include <string>
#include "types/StealthKey.hpp"
#include "GenericKeyValidator.hpp"

namespace Xeth{


class StealthKeyUnlocker
{
    public:
        void operator()(StealthKey &, const std::string &password) const;
};


typedef GenericKeyValidator<StealthKey, StealthKeyUnlocker> StealthKeyValidator;

}
