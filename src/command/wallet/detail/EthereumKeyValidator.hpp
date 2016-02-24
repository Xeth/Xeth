#pragma once 

#include <string>

#include "types/EthereumKey.hpp"


namespace Xeth{


class EthereumKeyValidator
{
    public:
        EthereumKeyValidator(const std::string &password);

        bool operator()(EthereumKey &) const;

    private:
        std::string _password;

};

}
