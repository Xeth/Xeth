#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "database/DataBase.hpp"

#include "SendToAddressCommand.hpp"
#include "SendToStealthCommand.hpp"


namespace Xeth{


class SendCommand
{
    public:
        SendCommand(Ethereum::Connector::Provider &provider, DataBase &database);

        QVariant operator ()(const QVariantMap &);

    private:
        template<class Command>
        QVariant send
        (
            Command &command,
            const std::string &from, 
            const std::string &to,
            const std::string &password,
            const BigInt &,
            const QVariant &gas,
            bool strict
        );

    private:
        Ethereum::Connector::Provider &_provider;
        DataBase &_database;

};


}
