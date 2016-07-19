
namespace Xeth{


template<class AccountsFetcher, class DataBase>
GenericAccountsLoader<AccountsFetcher, DataBase>::GenericAccountsLoader(const AccountsFetcher &fetcher, const DataBase &database) :
    _accountsFetcher(fetcher),
    _database(database)
{}


template<class AccountsFetcher, class DataBase>
bool GenericAccountsLoader<AccountsFetcher, DataBase>::load(ChainScanner &scanner, BalanceObserver &balanceObserver)
{
    const typename DataBase::StealthKeyStore & stealthKeys = _database.getStealthKeys();
    const typename DataBase::BitProfileStore & bitprofileStore = _database.getBitProfiles();
    const typename DataBase::StealthPaymentStore & stealthPayments = _database.getStealthPayments();

    try
    {
        typename AccountsFetcher::Result accounts = _accountsFetcher.getAccounts();

        std::set<std::string> skipped;

        for(typename DataBase::StealthPaymentStore::Iterator it=stealthPayments.begin(), end=stealthPayments.end(); it!=end; ++it)
        {
            QJsonObject payment = *it;
            skipped.insert(payment["address"].toString().toStdString());
        }

        for(typename DataBase::BitProfileStore::Iterator it=bitprofileStore.begin(), end=bitprofileStore.end(); it!=end; ++it)
        {
            scanner.loadAddress(it->getAuthAddress());
        }


        for(typename AccountsFetcher::Result::Iterator it = accounts.begin(), end=accounts.end(); it!=end; ++it)
        {
            std::string address = *it;
            if(skipped.find(address)==skipped.end())
            {
                scanner.loadAddress(address);
                balanceObserver.watch(address);
            }
        }

        for(typename DataBase::StealthKeyStore::Iterator it=stealthKeys.begin(), end=stealthKeys.end(); it!=end; ++it)
        {
            scanner.loadStealthAddress(*it);
        }
    }
    catch(...)
    {
        return false;
    }

    return true;
}


}
