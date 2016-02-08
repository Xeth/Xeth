#pragma once

#include <QString>

namespace Xeth{


class AddressValidator
{
    public:


        bool validateAddress(const std::string &);
        bool validateStealth(const std::string &);

};


class StealthAddressValidator
{
    public:
        bool operator()(const std::string &);
};


class HexAddressValidator
{
    public:
        bool operator()(const std::string &);
};


}
