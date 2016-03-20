#pragma once

#include <QVariantList>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "database/DataBase.hpp"
#include "types/EthereumKey.hpp"



namespace Xeth{


class GetAccountsCommand
{
    public:
        GetAccountsCommand(Ethereum::Connector::Provider &, const DataBase &);

        QVariant operator()();

    private:
        QString computeCheckSum(const std::string &);

    private:
        Ethereum::Connector::Provider &_provider;
        const DataBase &_database;
};



}
