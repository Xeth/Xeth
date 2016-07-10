#include "WalletFacade.hpp"
#include <QDebug>


namespace Xeth{

WalletFacade::WalletFacade
(
    const Settings &settings, 
    Ethereum::Connector::Provider &provider, 
    DataBase &database, 
    Notifier &notifier, 
    Synchronizer &synchronizer,
    Invoker<Notifier> &invoker
) :
    _settings(settings),
    _invoker(invoker),
    _provider(provider),
    _database(database),
    _notifier(notifier),
    _synchronizer(synchronizer)
{
    QObject::connect(&synchronizer.getBalanceObserver(), &BalanceObserver::Update, this, &WalletFacade::emitBalance);
    QObject::connect(&database.getEthereumKeys(), &EthereumKeyStore::Key, this, &WalletFacade::emitEthereumKey);
    QObject::connect(&database.getStealthKeys(), &StealthKeyStore::Key, this, &WalletFacade::emitStealthKey);
    QObject::connect(&database.getStealthPayments(), &StealthPaymentStore::NewItem, this, &WalletFacade::emitStealthPayment);
    QObject::connect(&database.getTransactions(), &TransactionStore::NewItem, this, &WalletFacade::emitTransaction);
}

void WalletFacade::emitTransaction(const QJsonObject &tx)
{
    emit Transaction(tx.toVariantMap());
}


void WalletFacade::emitBalance(const QString &address, const BigInt &unconfirmed, const BigInt &confirmed)
{
    emit Balance(address, QString(unconfirmed.str().c_str()), QString(confirmed.str().c_str()));
}


void WalletFacade::emitStealthKey(const QString &address)
{
    QVariantMap account;
    account.insert("stealth", address);
    emit Account(account);

}

void WalletFacade::emitStealthPayment(const QJsonObject &payment)
{
    QVariantMap account;
    EthereumCheckSum checksum;
    account.insert("stealth", payment["stealth"].toString());
    account.insert("address", QString(checksum.compute(payment["address"].toString().toStdString()).c_str()));
    emit Account(account);
}


void WalletFacade::emitEthereumKey(const QString &address)
{
    if(!_database.getStealthPayments().get(address.toStdString()).empty())
    {
        return; //ignore duplicates
    }
    QVariantMap account;
    EthereumCheckSum checksum;
    account.insert("address", QString(checksum.compute(address.toStdString()).c_str()));
    emit Account(account);
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

QVariant WalletFacade::getPendingBalance(const QString &address)
{
    GetPendingBalanceCommand command(_provider);
    return _invoker.invoke(command, address);
}

QObject * WalletFacade::getBalanceAsync(const QString &address)
{
    GetBalanceCommand command(_provider);
    return _invoker.invokeAsync(command, address);
}

QObject * WalletFacade::getPendingBalanceAsync(const QString &address)
{
    GetPendingBalanceCommand command(_provider);
    return _invoker.invokeAsync(command, address);
}

QVariant WalletFacade::send(const QVariantMap &request)
{
    SendCommand command(_provider, _database);
    return _invoker.invoke(command, request);
}

QObject * WalletFacade::sendAsync(const QVariantMap &request)
{
    SendCommand command(_provider, _database);
    return _invoker.invokeAsync(command, request);
}

QVariant WalletFacade::listTransactions(const QVariantMap &request)
{
    ListTransactionsCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::importKey(const QVariantMap &request)
{
    ImportKeyCommand command(_settings, _database, _synchronizer, _notifier);
    return _invoker.invoke(command, request);
}


QObject * WalletFacade::importKeyAsync(const QVariantMap &request)
{
    ImportKeyCommand command(_settings, _database, _synchronizer, _notifier);
    return _invoker.invokeAsync(command, request);
}


QVariant WalletFacade::exportKey(const QVariantMap &request)
{
    ExportKeyCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::generateKey(const QVariantMap &request)
{
    GenerateKeyCommand command(_database, _synchronizer);
    return _invoker.invoke(command, request);
}

QObject * WalletFacade::generateKeyAsync(const QVariantMap &request)
{
    GenerateKeyCommand command(_database, _synchronizer);
    return _invoker.invokeAsync(command, request);
}


QVariant WalletFacade::validateAddress(const QString &request)
{
    ValidateAddressCommand command;
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::validateAddress(const QVariantMap &request)
{
    ValidateAddressCommand command;
    return _invoker.invoke(command, request);
}



QVariant WalletFacade::changePassword(const QVariantMap &request)
{
    ChangeKeyPasswordCommand command(_database);
    return _invoker.invoke(command, request);
}

QObject * WalletFacade::changePasswordAsync(const QVariantMap &request)
{
    ChangeKeyPasswordCommand command(_database);
    return _invoker.invokeAsync(command, request);
}

QVariant WalletFacade::estimateFee(const QVariantMap &request)
{
    EstimateFeeCommand command(_provider);
    return _invoker.invoke(command, request);
}


}
