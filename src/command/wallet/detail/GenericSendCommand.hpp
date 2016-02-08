#pragma once 

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include <QString>
#include <QVariant>

#include <boost/multiprecision/cpp_dec_float.hpp>

#include "database/DataBase.hpp"
#include "types/BigInt.hpp"

#include "AddressValidator.hpp"

namespace Xeth{


template<class Sender, class Validator>
class GenericSendCommand
{
    public:

        GenericSendCommand(Ethereum::Connector::Provider &provider);
        QVariant operator()(const QVariantMap &);

    private:
        Ethereum::Connector::Wallet _wallet;

};


}

#include "GenericSendCommand.ipp"
