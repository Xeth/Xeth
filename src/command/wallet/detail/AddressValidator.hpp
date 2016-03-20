#pragma once

#include <QString>
#include "types/EthereumKey.hpp"

namespace Xeth{


class AddressValidator
{
    public:


        bool validateAddress(const std::string &, bool);
        bool validateStealth(const std::string &, bool);

};


class StealthAddressValidator
{
    public:
        bool operator()(const std::string &, bool strict=false);
};


class HexAddressValidator
{
    public:
        bool operator()(const std::string &, bool strict=false);
};


}
