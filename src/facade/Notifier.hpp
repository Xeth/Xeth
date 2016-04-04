#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantMap>
#include <QJsonObject>

#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"

namespace Xeth{


class Notifier : public QObject
{
    Q_OBJECT
    public:

        Notifier();

        void watch(const DataBase &);
        void watch(const Synchronizer &);

    public slots:
        void emitObjectError(const QString &context, const QString &uri, const QString &msg);
        void emitError(const QString &context, const QString &msg);
        void emitError(const QString &);
        void emitMessage(const QString &);
        void emitReady();

        void emitData(const QString &context, const QString &uri, const QString &key, const QString &value);
        void emitData(const QString &context, const QString &key, const QString &value);

    signals:
        void Ready() const;
        void Error(const QVariantMap &) const;
        void Message(const QString &) const;
        void Data(const QVariantMap &) const;

        void Profile(const QVariantMap &) const;
        void ProfileRename(const QVariantMap &) const;

        void Transaction(const QVariantMap &) const;
        void ScanProgress(const QVariant &) const;
        void SyncProgress(const QVariant &) const;
        void Account(const QVariantMap &) const;
        void Contact(const QVariantMap &) const;
        void Config(const QString &, const QString &) const;


    private slots:
        void emitAddressBookItem(const QJsonObject &);
        void emitEthereumKey(const QString &);
        void emitStealthPayment(const QJsonObject &);
        void emitStealthKey(const QString &);
        void emitTransaction(const QJsonObject &);
        void emitScanProgress(double);
        void emitSyncProgress(double);
        void emitConfig(const QString &, const QString &);
        void emitProfile(const BitProfile::ProfileDescriptor &);
        void emitProfileRename(const QString &old, const BitProfile::ProfileDescriptor &);

    private:
        const DataBase *_database;
};


}
