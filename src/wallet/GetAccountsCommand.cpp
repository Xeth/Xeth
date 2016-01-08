#include "GetAccountsCommand.hpp"

namespace Xeth{

GetAccountsCommand::GetAccountsCommand(Ethereum::Connector::Provider &provider, DataBase &database):
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
        obj["stealth"] = false;
        accounts.push_back(obj);
    }

    return QVariant::fromValue(accounts);
}

}
