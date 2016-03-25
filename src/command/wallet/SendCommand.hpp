#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "database/DataBase.hpp"

#include "detail/AddressValidator.hpp"
#include "detail/Sender.hpp"
#include "detail/GenericSendCommand.hpp"
#include "types/StealthKey.hpp"



namespace Xeth{

typedef GenericSendCommand<AddressSender, HexAddressValidator> SendToAddressCommand;
typedef GenericSendCommand<StealthSender, StealthAddressValidator> SendToStealthCommand;


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
            const QVariant &price,
            bool strict
        );

    private:
        Ethereum::Connector::Provider &_provider;
        DataBase &_database;

};


}
