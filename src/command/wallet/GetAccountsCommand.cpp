#include "GetAccountsCommand.hpp"

namespace Xeth{

GetAccountsCommand::GetAccountsCommand(Ethereum::Connector::Provider &provider, const DataBase &database):
    _provider(provider),
    _database(database)
{}

QVariant GetAccountsCommand::operator ()()
{
    QVariantList accounts;

    Ethereum::Connector::Wallet wallet(_provider);
    Ethereum::Connector::Collection<std::string> addresses = wallet.getAccounts();

    for(Ethereum::Connector::Collection<std::string>::Iterator it=addresses.begin(), end=addresses.end(); it!=end; ++it)
    {
        QVariantMap obj;
        obj["address"] = it->c_str();
        accounts.push_back(obj);
    }

    const StealthKeyStore & stealthKeys = _database.getStealthKeys();

    for(StealthKeyStore::Iterator it = stealthKeys.begin(), end = stealthKeys.end(); it!=end; ++it)
    {
        try
        {
            Ethereum::Stealth::Address address(*it);
            QVariantMap obj;
            obj["address"] = address.toString().c_str();
            obj["stealth"] = true;
            accounts.push_back(obj);
        }
        catch(...)
        {}
    }

    return QVariant::fromValue(accounts);
}

}
