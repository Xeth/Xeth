#pragma once

#include <QVariantList>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "DataBase.hpp"




namespace Xeth{


class GetAccountsCommand
{
    public:
        GetAccountsCommand(Ethereum::Connector::Provider &, DataBase &);

        QVariant operator()();

    private:
        Ethereum::Connector::Provider &_provider;
        DataBase &_database;
};



}
