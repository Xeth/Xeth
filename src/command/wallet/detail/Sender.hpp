#pragma once 

#include <string>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "types/BigInt.hpp"
#include "types/StealthKey.hpp"
#include "types/EthereumKey.hpp"

namespace Xeth{

class AddressSender
{
    public:
        std::string operator()(Ethereum::Connector::Wallet &, const std::string &from, const std::string &to, const BigInt &amount);
};

class StealthSender
{
    public:
        std::string operator()(Ethereum::Connector::Wallet &, const std::string &from, const std::string &to, const BigInt &amount);
};

}
