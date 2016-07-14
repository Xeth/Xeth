#pragma once 

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "database/DataBase.hpp"

#include "ChainScanner.hpp"
#include "BalanceObserver.hpp"


namespace Xeth{


class AccountsLoader
{
    private:
        typedef Ethereum::Connector::Collection<std::string> AccountsList;

    public:
        AccountsLoader(Ethereum::Connector::Provider &connector, const DataBase &database);

        bool load(ChainScanner &, BalanceObserver &);

    private:
        Ethereum::Connector::Provider &_provider;
        const DataBase &_database;
};



}

