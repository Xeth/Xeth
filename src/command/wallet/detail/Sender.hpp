#pragma once 

#include <string>
#include <time.h>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "types/BigInt.hpp"
#include "types/StealthKey.hpp"
#include "types/EthereumKey.hpp"

#include "database/TransactionObjectBuilder.hpp"

namespace Xeth{


class Sender
{
    public:
        Sender();

        BigInt getGas();
        BigInt getGasPrice();
        void setGasLimit(const BigInt &gas);
        void setGasPrice(const BigInt &gas);
        void unsetGasLimit();
        void unsetGasPrice();
        bool hasGasPrice();
        bool hasGas();

    protected:
        inline std::string send
        (
            Ethereum::Connector::Wallet &,
            TransactionObjectBuilder &,
            const std::string &from,
            const std::string &to,
            const BigInt &amount,
            const std::string &data
        );

        inline std::string send
        (
            Ethereum::Connector::Wallet &,
            const std::string &from,
            const std::string &to,
            const BigInt &amount,
            const std::string &data
        );

    private:
        BigInt _gas;
        BigInt _price;
        bool _hasGas;
        bool _hasGasPrice;
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
