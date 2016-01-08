#pragma once

#include <eth-connector/Provider.hpp>
#include <eth-connector/Wallet.hpp>

#include <QString>
#include <QVariant>

#include <boost/multiprecision/cpp_dec_float.hpp>

#include "DataBase.hpp"
#include "BigInt.hpp"

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
