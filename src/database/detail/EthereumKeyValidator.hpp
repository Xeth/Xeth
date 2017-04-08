#pragma once 

#include <string>
#include "types/EthereumKey.hpp"
#include "GenericKeyValidator.hpp"


namespace Xeth{


class EthereumKeyUnlocker
{
    public:
        void operator()(EthereumKey &, const std::string &password) const;
};


typedef GenericKeyValidator<EthereumKey, EthereumKeyUnlocker> EthereumKeyValidator;


}
