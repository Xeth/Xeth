#pragma once 

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "database/DataBase.hpp"

#include "ScanCriteria.hpp"
#include "AccountScanCriterion.hpp"
#include "StealthScanCriterion.hpp"



namespace Xeth{


template<class AccountsFetcher, class DataBase>
class GenericScanCriteriaLoader
{
    public:

        GenericScanCriteriaLoader(const AccountsFetcher &, const DataBase &);
        bool load(ScanCriteria &);


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



class ScanCriteriaLoader : public GenericScanCriteriaLoader<AccountsFetcher, DataBase>
{
    public:
        typedef GenericScanCriteriaLoader<AccountsFetcher, DataBase> Base;

    public:
        ScanCriteriaLoader(Ethereum::Connector::Provider &connector, const DataBase &database);

};


}

#include "ScanCriteriaLoader.ipp"
