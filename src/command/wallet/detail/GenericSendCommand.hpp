#pragma once 

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include <QString>
#include <QVariant>

#include "database/DataBase.hpp"
#include "database/TransactionObjectBuilder.hpp"
#include "types/BigInt.hpp"

#include "AddressValidator.hpp"
#include "detail/StealthSpendKeyRedeemer.hpp"


namespace Xeth{


template<class Sender, class Validator, class Estimator>
class GenericSendCommand
{
    public:

        GenericSendCommand(Ethereum::Connector::Provider &provider, DataBase &database);
        QVariant operator()(const QVariantMap &);

        QVariant operator()
        (
            const QString &from,
            const QString &to,
            const QString &password,
            const QString &amount,
            const QVariant &logs,
            bool strict = true
        );
        QVariant operator()
        (
            const QString &from,
            const QString &to,
            const QString &password,
            const QString &amount,
            const QString &gas,
            const QString &price,
            const QVariant &logs,
            bool strict = true
        );

    private:
        bool validateDestination(const std::string &, bool strict);
        QVariant send(const QString &from, const QString &to, const QString &password, const QString &amount, const QVariant &logs, bool strict);
        QVariant send(const std::string &from, const std::string &to, const std::string &password, const std::string &amount, const QVariant &logs, bool strict);

    private:
        Ethereum::Connector::Wallet _wallet;
        Sender _sender;
        DataBase &_database;
        Estimator _estimator;

};


}

#include "GenericSendCommand.ipp"
