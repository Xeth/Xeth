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
{
    QObject::connect(&_synchronizer.getScanner(), &ChainScanner::Transaction, &notifier, &Notifier::emitTransaction);
}

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
    SendToAddressCommand command(_provider, _database);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::sendToStealth(const QVariantMap &request)
{
    SendToStealthCommand command(_provider, _database);
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


QVariant WalletFacade::generateKey(const QVariantMap &request)
{
    GenerateKeyCommand command(_database, _synchronizer);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::generateStealthKey(const QVariantMap &request)
{
    GenerateStealthKeyCommand command(_database, _synchronizer);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::validateAddress(const QVariantMap &request)
{
    ValidateAddressCommand command;
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::validateStealthAddress(const QVariantMap &request)
{
    ValidateStealthAddressCommand command;
    return _invoker.invoke(command, request);
}

}
