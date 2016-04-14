namespace Xeth{


template<class AccountsFetcher, class DataBase>
GenericScanCriteriaLoader<AccountsFetcher, DataBase>::GenericScanCriteriaLoader(const AccountsFetcher &fetcher, const DataBase &database) :
    _accountsFetcher(fetcher),
    _database(database)
{}


template<class AccountsFetcher, class DataBase>
bool GenericScanCriteriaLoader<AccountsFetcher, DataBase>::load(ScanCriteria &criteria)
{
    const typename DataBase::ScanIndexStore &indexStore = _database.getScanIndex();
    const typename DataBase::StealthKeyStore & stealthKeys = _database.getStealthKeys();
    const typename DataBase::StealthPaymentStore & stealthPayments = _database.getStealthPayments();

    std::set<std::string> accountsRegistry;

    try
    {
        typename AccountsFetcher::Result accounts = _accountsFetcher.getAccounts();

        for(typename AccountsFetcher::Result::Iterator it = accounts.begin(), end=accounts.end(); it!=end; ++it)
        {
            std::string address = *it;
            size_t cursor = indexStore.get(address.c_str());
            criteria.addCriterion<AccountScanCriterion>(cursor, address.c_str());
            accountsRegistry.insert(address);
        }

        for(typename DataBase::StealthKeyStore::Iterator it=stealthKeys.begin(), end=stealthKeys.end(); it!=end; ++it)
        {
            StealthKey key = *it;
            Ethereum::Stealth::Address address(key);
            size_t cursor = indexStore.get(address.toString().c_str());
            criteria.addCriterion<StealthScanCriterion>(cursor, key, address);
        }
    }
    catch(...)
    {
        return false;
    }

    return true;
}


}
