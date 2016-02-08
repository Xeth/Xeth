#pragma once 

#include <string>
#include <time.h>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "types/BigInt.hpp"
#include "types/StealthKey.hpp"
#include "types/EthereumKey.hpp"

#include "database/DataBase.hpp"

namespace Xeth{

class AddressSender
{
    public:
        std::string operator()
        (
            Ethereum::Connector::Wallet &,
            DataBase &,
            const std::string &from,
            const std::string &to,
            const BigInt &amount
        );

        std::string operator()
        (
            Ethereum::Connector::Wallet &,
            DataBase &,
            const std::string &from,
            const std::string &to,
            const BigInt &amount,
            const BigInt &gas
        );

};

class StealthSender
{
    public:
        std::string operator()
        (
            Ethereum::Connector::Wallet &,
            DataBase &,
            const std::string &from,
            const std::string &to,
            const BigInt &amount
        );

        std::string operator()
        (
            Ethereum::Connector::Wallet &,
            DataBase &,
            const std::string &from,
            const std::string &to,
            const BigInt &amount,
            const BigInt &gas
        );

};

}
