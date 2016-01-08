#pragma once

#include <QVariantList>
#include <QVariantMap>

#include <eth-connector/Provider.hpp>
#include <eth-connector/Wallet.hpp>

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
