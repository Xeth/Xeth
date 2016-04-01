#pragma once 

#include <string>
#include <time.h>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "types/BigInt.hpp"
#include "types/StealthKey.hpp"
#include "types/EthereumKey.hpp"

#include "TransactionObjectBuilder.hpp"

namespace Xeth{


class Sender
{
    public:
        void setGasLimit(const BigInt &gas);
        void setGasPrice(const BigInt &gas);

    protected:
        inline std::string send
        (
            Ethereum::Connector::Wallet &,
            TransactionObjectBuilder &,
            const std::string &from,
            const std::string &to,
            const BigInt &amount
        );

    private:
        BigInt _gas;
        BigInt _price;
};


class AddressSender : public Sender
{
    public:
        std::string operator()
        (
            Ethereum::Connector::Wallet &,
            TransactionObjectBuilder &,
            const std::string &from,
            const std::string &to,
            const BigInt &amount
        );

};

class StealthSender : public Sender
{
    public:
        std::string operator()
        (
            Ethereum::Connector::Wallet &,
            TransactionObjectBuilder &,
            const std::string &from,
            const std::string &to,
            const BigInt &amount
        );
};

}
