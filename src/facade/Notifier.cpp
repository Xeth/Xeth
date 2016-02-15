#include "Notifier.hpp"

namespace Xeth{


void Notifier::watch(const DataBase &database)
{
    QObject::connect(&database.getTransactions(), &TransactionStore::NewItem, this, &Notifier::emitTransaction);
    QObject::connect(&database.getEthereumKeys(), &EthereumKeyStore::NewItem, this, &Notifier::emitEthereumKey);
    QObject::connect(&database.getStealthKeys(), &StealthKeyStore::NewItem, this, &Notifier::emitStealthKey);
    QObject::connect(&database.getAddressBook(), &AddressBookStore::NewItem, this, &Notifier::emitAddressBookItem);
}

void Notifier::watch(const Synchronizer &synchronizer)
{
    QObject::connect(&synchronizer.getScanner().getProgress(), &Synchronizer::ScanProgress::Progress, this, &Notifier::emitScanProgress);
    QObject::connect(&synchronizer.getSyncProgressFetcher(), &Synchronizer::SyncProgress::Progress, this, &Notifier::emitSyncProgress);
}

void Notifier::emitError(const QString &msg)
{
    emit Error(msg);
}


void Notifier::emitMessage(const QString &msg)
{
    emit Message(msg);
}


void Notifier::emitReady()
{
    emit Ready();
}


void Notifier::emitTransaction(const QJsonObject &tx)
{
    emit Transaction(tx.toVariantMap());
}


void Notifier::emitScanProgress(double progress)
{
    emit ScanProgress(QVariant::fromValue(progress));
}


void Notifier::emitSyncProgress(double progress)
{
    emit SyncProgress(QVariant::fromValue(progress));
}

void Notifier::emitStealthKey(const QString &address)
{
    QVariantMap account;
    account.insert("address", address);
    account.insert("stealth", true);

    emit Account(account);

}

void Notifier::emitEthereumKey(const QString &address)
{
    QVariantMap account;
    account.insert("address", address);
    emit Account(account);
}


void Notifier::emitAddressBookItem(const QJsonObject &item)
{
    emit Alias(item.toVariantMap());
}

}
