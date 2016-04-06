#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "database/DataBase.hpp"
#include "types/StealthKey.hpp"

#include "detail/AddressValidator.hpp"
#include "detail/Sender.hpp"
#include "detail/GenericSendCommand.hpp"
#include "detail/SendGasEstimator.hpp"


namespace Xeth{

typedef GenericSendCommand<AddressSender, HexAddressValidator, HexSendGasEstimator> SendToAddressCommand;
typedef GenericSendCommand<StealthSender, StealthAddressValidator, StealthSendGasEstimator> SendToStealthCommand;


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
            const QString &from, 
            const QString &to,
            const QString &password,
            const QString &,
            const QVariant &gas,
            const QVariant &price,
            const QVariant &logs,
            bool strict
        );

    private:
        Ethereum::Connector::Provider &_provider;
        DataBase &_database;

};


}
