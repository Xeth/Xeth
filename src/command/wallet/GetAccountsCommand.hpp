#pragma once

#include <QVariantList>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "database/DataBase.hpp"




namespace Xeth{


class GetAccountsCommand
{
    public:
        GetAccountsCommand(Ethereum::Connector::Provider &, const DataBase &);

        QVariant operator()();

    private:
        Ethereum::Connector::Provider &_provider;
        const DataBase &_database;
};



}
