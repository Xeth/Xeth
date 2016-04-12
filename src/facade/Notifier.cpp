#include "Notifier.hpp"

namespace Xeth{

Notifier::Notifier() : 
    _database(NULL)
{}

void Notifier::watch(const DataBase &database)
{
    _database = &database;
    QObject::connect(&database.getTransactions(), &TransactionStore::NewItem, this, &Notifier::emitTransaction);
    QObject::connect(&database.getEthereumKeys(), &EthereumKeyStore::NewItem, this, &Notifier::emitEthereumKey);
    QObject::connect(&database.getStealthKeys(), &StealthKeyStore::NewItem, this, &Notifier::emitStealthKey);
    QObject::connect(&database.getStealthPayments(), &StealthPaymentStore::NewItem, this, &Notifier::emitStealthPayment);
    QObject::connect(&database.getAddressBook(), &AddressBookStore::NewItem, this, &Notifier::emitAddressBookItem);
    QObject::connect(&database.getConfig(), &ConfigStore::Change, this, &Notifier::emitConfig);
    QObject::connect(&database.getBitProfiles(), &BitProfileStore::NewItem, this, &Notifier::emitProfile);
    QObject::connect(&database.getBitProfiles(), &BitProfileStore::Renamed, this, &Notifier::emitProfileRename);
}

void Notifier::watch(const Synchronizer &synchronizer)
{
    QObject::connect(&synchronizer.getScanner().getProgress(), &Synchronizer::ScanProgress::Progress, this, &Notifier::emitScanProgress);
    QObject::connect(&synchronizer.getSyncProgressFetcher(), &Synchronizer::SyncProgress::Progress, this, &Notifier::emitSyncProgress);
}

void Notifier::emitData(const QString &context, const QString &uri, const QString &key, const QVariant &value)
{
    QVariantMap event;
    event["context"] = context;
    event["uri"] = uri;
    event["key"] = key;
    event["value"] = value;
    emit Data(event);
}


void Notifier::emitData(const QString &context, const QString &key, const QVariant &value)
{
    QVariantMap event;
    event["context"] = context;
    event["key"] = key;
    event["value"] = value;
    emit Data(event);
}



void Notifier::emitProfileRename(const QString &oldURI, const BitProfile::ProfileDescriptor &descriptor)
{
    QVariantMap event;
    event["oldURI"] = oldURI;
    event["uri"] = descriptor.getURI().c_str();
    event["context"] = descriptor.getContext().c_str();
    event["id"] = descriptor.getName().c_str();
    emit ProfileRename(event);
}

void Notifier::emitProfile(const BitProfile::ProfileDescriptor &descriptor)
{
    QVariantMap event;
    event["id"] = descriptor.getName().c_str();
    event["uri"] = descriptor.getURI().c_str();
    event["context"] = descriptor.getContext().c_str();
    event["account"] = descriptor.getAuthAddress().c_str();
    emit Profile(event);
}

void Notifier::emitConfig(const QString &name, const QString &value)
{
    emit Config(name, value);
}

void Notifier::emitError(const QString &msg)
{
    QVariantMap event;
    event["message"] = msg;
    emit Error(event);
}

void Notifier::emitError(const QString &context, const QString &msg)
{
    QVariantMap event;
    event["context"] = context;
    event["message"] = msg;
    emit Error(event);
}

void Notifier::emitObjectError(const QString &context, const QString &uri, const QString &msg)
{
    QVariantMap event;
    event["context"] = context;
    event["message"] = msg;
    event["uri"] = uri;
    emit Error(event);
}


void Notifier::emitMessage(const QString &msg)
{
    emit Message(msg);
}


void Notifier::emitReady()
{
    qDebug()<<"emitting ready signal";
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
    account.insert("stealth", address);
    emit Account(account);

}

void Notifier::emitStealthPayment(const QJsonObject &payment)
{
    QVariantMap account;
    EthereumCheckSum checksum;
    account.insert("stealth", payment["stealth"].toString());
    account.insert("address", QString(checksum.compute(payment["address"].toString().toStdString()).c_str()));
    emit Account(account);
}

void Notifier::emitEthereumKey(const QString &address)
{
    if(_database)
    {
        const StealthPaymentStore & store = _database->getStealthPayments();
        if(!store.get(address.toStdString()).empty())
        {
            return; //ignore duplicates
        }
    }
    QVariantMap account;
    EthereumCheckSum checksum;
    account.insert("address", QString(checksum.compute(address.toStdString()).c_str()));
    emit Account(account);
}


void Notifier::emitAddressBookItem(const QJsonObject &item)
{
    emit Contact(item.toVariantMap());
}

}
