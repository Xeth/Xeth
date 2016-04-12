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

    std::map<QString, bool> registry;

    const StealthPaymentStore & stealthPayments = _database.getStealthPayments();
    for(StealthPaymentStore::Iterator it=stealthPayments.begin(), end=stealthPayments.end(); it!=end; ++it)
    {
        QString address = computeCheckSum((*it)["address"].toString().toStdString());
        registry.insert(std::make_pair(address, true));

//        if(wallet.getBalance(address.toStdString())!=0)
//        {
            QVariantMap obj;
            obj["address"] = address;
            obj["stealth"] = it->take("stealth");
            accounts.push_back(obj);
//        }
    }


    for(Ethereum::Connector::Collection<std::string>::Iterator it=addresses.begin(), end=addresses.end(); it!=end; ++it)
    {
        QString address = computeCheckSum(*it);
        if(registry.find(address)==registry.end())
        {
            QVariantMap obj;
            obj["address"] = address;
            accounts.push_back(obj);
        }
    }

    const StealthKeyStore & stealthKeys = _database.getStealthKeys();

    for(StealthKeyStore::Iterator it = stealthKeys.begin(), end = stealthKeys.end(); it!=end; ++it)
    {
        try
        {
            Ethereum::Stealth::Address address(*it);
            QVariantMap obj;
            obj["stealth"] = address.toString().c_str();
            accounts.push_back(obj);
        }
        catch(...)
        {}
    }


    return QVariant::fromValue(accounts);
}

QString GetAccountsCommand::computeCheckSum(const std::string &hex)
{
    EthereumCheckSum checksum;
    return QString(checksum.compute(hex).c_str());
}

}
