#include "AccountsLoader.hpp"


namespace Xeth{


AccountsLoader::AccountsLoader(Ethereum::Connector::Provider &provider, const DataBase &database):
   _provider(provider),
   _database(database)
{}


bool AccountsLoader::load(ChainScanner &scanner, BalanceObserver &balanceObserver)
{
    const DataBase::StealthKeyStore & stealthKeys = _database.getStealthKeys();
    const DataBase::BitProfileStore & bitprofileStore = _database.getBitProfiles();
    const DataBase::StealthPaymentStore & stealthPayments = _database.getStealthPayments();
    Ethereum::Connector::Wallet wallet(_provider);
    Ethereum::Connector::BlockChain chain(_provider);

    Ethereum::Connector::Block lastBlock = chain.getBlock(chain.getHeight());
    time_t lastBlockTime = lastBlock.getTimestamp();

    try
    {
        AccountsList accounts = wallet.getAccounts();

        std::set<std::string> skipped;

        for(DataBase::StealthPaymentStore::Iterator it=stealthPayments.begin(), end=stealthPayments.end(); it!=end; ++it)
        {
            QJsonObject payment = *it;
            std::string address = payment["address"].toString().toStdString();
            if(wallet.getBalance(address) == 0 && (!payment["timestamp"].isNull() && payment["timestamp"].toInt() < lastBlockTime))
            {
                skipped.insert(address);
            }
        }

        for(DataBase::BitProfileStore::Iterator it=bitprofileStore.begin(), end=bitprofileStore.end(); it!=end; ++it)
        {
            scanner.loadAddress(it->getAuthAddress());
        }


        for(AccountsList::Iterator it = accounts.begin(), end=accounts.end(); it!=end; ++it)
        {
            std::string address = *it;
            if(skipped.find(address)==skipped.end())
            {
                scanner.loadAddress(address);
                balanceObserver.watch(address);
            }
        }

        for(DataBase::StealthKeyStore::Iterator it=stealthKeys.begin(), end=stealthKeys.end(); it!=end; ++it)
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
