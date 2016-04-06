#pragma once 

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include <QString>
#include <QVariant>

#include "database/DataBase.hpp"
#include "database/TransactionObjectBuilder.hpp"
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
            const QVariant &logs,
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
            const QVariant &logs,
            bool strict = true
        );

    private:
        bool validateDestination(const std::string &, bool strict);
        bool unlockSender(const std::string &, const std::string &);
        QVariant send(const std::string &from, const std::string &to, const std::string &password, const BigInt &amount, const QVariant &logs, bool strict);

    private:
        Ethereum::Connector::Wallet _wallet;
        Sender _sender;
        DataBase &_database;

};


}

#include "GenericSendCommand.ipp"
