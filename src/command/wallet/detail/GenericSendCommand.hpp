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

    private:
        Ethereum::Connector::Wallet _wallet;
        DataBase &_database;

};


}

#include "GenericSendCommand.ipp"
