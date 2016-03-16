#pragma once

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include <QString>
#include <QVariant>

#include <boost/multiprecision/cpp_dec_float.hpp>

#include "../../../types/Enum.hpp"

namespace Xeth{

DECLARE_ENUM_CLASS(BalanceType, pending, latest, earliest);

template<BalanceType::Value type>
class GenericGetBalanceCommand
{
    public:

        GenericGetBalanceCommand(Ethereum::Connector::Provider &);

        QVariant operator()(const QString &);
        QVariant operator()(const char *);


    private:
        Ethereum::Connector::Wallet _wallet;
};


}
