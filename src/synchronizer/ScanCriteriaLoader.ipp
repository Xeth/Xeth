
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
            std::string address = it->getAuthAddress();
            size_t cursor = indexStore.get(address.c_str());
            criteria.addCriterion<AccountScanCriterion>(cursor, address.c_str());
        }


        for(typename AccountsFetcher::Result::Iterator it = accounts.begin(), end=accounts.end(); it!=end; ++it)
        {
            std::string address = *it;
            if(skipped.find(address)==skipped.end())
            {
                size_t cursor = indexStore.get(address.c_str());
                criteria.addCriterion<AccountScanCriterion>(cursor, address.c_str());
            }
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
