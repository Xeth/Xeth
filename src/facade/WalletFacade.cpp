#include "WalletFacade.hpp"
#include <QDebug>


namespace Xeth{

WalletFacade::WalletFacade(const Settings &settings, Ethereum::Connector::Provider &provider, DataBase &database, Notifier &notifier) :\
    _settings(settings),
    _invoker(notifier),
    _provider(provider),
    _database(database)
{}

QVariant WalletFacade::getAccounts()
{
    GetAccountsCommand command(_provider, _database);
    return _invoker.invoke(command, NullCommandArguments());
}

QVariant WalletFacade::getBalance(const QString &address)
{
    GetBalanceCommand command(_provider);
    return _invoker.invoke(command, address);
}

QVariant WalletFacade::sendToAddress(const QVariantMap &request)
{
    SendToAddressCommand command(_provider);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::listTransactions(const QVariantMap &request)
{
    ListTransactionsCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::getTransaction(const QString &hash)
{
    GetTransactionCommand command(_database);
    return _invoker.invoke(command, hash);
}


QVariant WalletFacade::importKey(const QVariantMap &request)
{
    ImportKeyCommand command(_settings);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::exportKey(const QVariantMap &request)
{
    ExportKeyCommand command(_database);
    return _invoker.invoke(command, request);
}



}
