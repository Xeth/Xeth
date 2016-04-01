#pragma once 

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include <QString>
#include <QVariant>

#include "database/DataBase.hpp"
#include "types/BigInt.hpp"

#include "AddressValidator.hpp"
#include "StealthRedeemKeyFactory.hpp"


namespace Xeth{


template<class Sender, class Validator>
class GenericSendCommand
{
    public:

        GenericSendCommand(Ethereum::Connector::Provider &provider, DataBase &database);
        QVariant operator()(const QVariantMap &);

        QVariant operator()
        (
            const std::string &from,
            const std::string &to,
            const std::string &password,
            const BigInt &amount,
            bool strict = true
        );
        QVariant operator()
        (
            const std::string &from,
            const std::string &to,
            const std::string &password,
            const BigInt &amount,
            const BigInt &gas,
            const BigInt &price,
            bool strict = true
        );

    private:
        bool validateDestination(const std::string &, bool strict);
        bool unlockSender(const std::string &, const std::string &, const BigInt &);
        QVariant send(const std::string &from, const std::string &to, const std::string &password, const BigInt &amount, bool strict);

    private:
        Ethereum::Connector::Wallet _wallet;
        Sender _sender;
        DataBase &_database;

};


}

#include "GenericSendCommand.ipp"
