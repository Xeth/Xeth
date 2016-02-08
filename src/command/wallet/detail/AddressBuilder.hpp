#pragma once 

#include "types/EthereumKey.hpp"
#include "types/StealthKey.hpp"

namespace Xeth{


class AddressBuilder
{
    public:
        std::string build(const EthereumKey &) const;
        std::string build(const StealthKey &) const;

};


}
