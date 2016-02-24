#pragma once 

#include <string>

#include "types/StealthKey.hpp"


namespace Xeth{


class StealthKeyValidator
{
    public:
        StealthKeyValidator(const std::string &);
        bool operator()(StealthKey &) const;

    private:
        std::string _password;
};


}
