#include "WalletFacade.hpp"
#include <QDebug>


namespace Xeth{

WalletFacade::WalletFacade
(
    const Settings &settings, 
    Ethereum::Connector::Provider &provider, 
    DataBase &database, 
    Notifier &notifier, 
    Synchronizer &synchronizer
) :
    _settings(settings),
    _invoker(notifier),
    _provider(provider),
    _database(database),
    _synchronizer(synchronizer)
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


QVariant WalletFacade::importPresaleKey(const QVariantMap &request)
{
    ImportPresaleKeyCommand command(_settings, _synchronizer);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::importKey(const QVariantMap &request)
{
    ImportKeyCommand command(_database, _synchronizer);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::importStealthKey(const QVariantMap &request)
{
    ImportStealthKeyCommand command(_database, _synchronizer);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::exportKey(const QVariantMap &request)
{
    ExportKeyCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::exportStealthKey(const QVariantMap &request)
{
    ExportStealthKeyCommand command(_database);
    return _invoker.invoke(command, request);
}


}
