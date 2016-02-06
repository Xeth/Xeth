#include "ScanCriteriaLoader.hpp"


namespace Xeth{


ScanCriteriaLoader::ScanCriteriaLoader(Ethereum::Connector::Provider &provider, const DataBase &database):
    Base(AccountsFetcher(provider), database)
{}


AccountsFetcher::AccountsFetcher(Ethereum::Connector::Provider &provider) :
    _provider(provider)
{}


AccountsFetcher::Result AccountsFetcher::getAccounts()
{
    Ethereum::Connector::Wallet wallet(_provider);
    return wallet.getAccounts();
}


}
