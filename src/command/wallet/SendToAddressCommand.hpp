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


class SendToAddressCommand
{
    public:

        SendToAddressCommand(Ethereum::Connector::Provider &);

        QVariant operator () (const QVariantMap &);


    private:
        Ethereum::Connector::Wallet _wallet;
        AddressValidator _validator;
};


}
