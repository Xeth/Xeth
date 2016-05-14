#pragma once 

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "database/DataBase.hpp"

#include "ChainScanner.hpp"
#include "BalanceObserver.hpp"


namespace Xeth{


template<class AccountsFetcher, class DataBase>
class GenericAccountsLoader
{
    public:
        GenericAccountsLoader(const AccountsFetcher &, const DataBase &);
        bool load(ChainScanner &, BalanceObserver &);

    private:
        AccountsFetcher _accountsFetcher;
        const DataBase &_database;

};



class AccountsFetcher
{
    public:
        typedef Ethereum::Connector::Collection<std::string> Result;

    public:
        AccountsFetcher(Ethereum::Connector::Provider &);
        Result getAccounts();

    private:
        Ethereum::Connector::Provider &_provider;
};



class AccountsLoader : public GenericAccountsLoader<AccountsFetcher, DataBase>
{
    public:
        typedef GenericAccountsLoader<AccountsFetcher, DataBase> Base;

    public:
        AccountsLoader(Ethereum::Connector::Provider &connector, const DataBase &database);

};


}

#include "AccountsLoader.ipp"
