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

        void watch(const DataBase &);
        void watch(const Synchronizer &);

        void emitError(const QString &);
        void emitMessage(const QString &);

        void emitReady();

    signals:
        void Ready() const;
        void Error(const QString &) const;
        void Message(const QString &) const;

        void Transaction(const QVariantMap &) const;
        void ScanProgress(const QVariant &) const;
        void SyncProgress(const QVariant &) const;
        void Account(const QVariantMap &) const;
        void Alias(const QVariantMap &) const;


    private slots:
        void emitAddressBookItem(const QJsonObject &);
        void emitEthereumKey(const QString &);
        void emitStealthKey(const QString &);
        void emitTransaction(const QJsonObject &);
        void emitScanProgress(double);
        void emitSyncProgress(double);


};


}
