#pragma once

#include <QObject>
#include <QString>
#include <QVariant>

namespace Xeth{


class Notifier : public QObject
{
    Q_OBJECT
    public:

        void emitError(const QString &);
        void emitMessage(const QString &);
        void emitTransaction(const QJsonObject &);
        void emitReady();
        void emitScanProgress(double);
        void emitSyncProgress(double);

    signals:
        void Error(const QString &) const;
        void Message(const QString &) const;
        void Ready() const;
        void Transaction(const QJsonObject &) const;
        void ScanProgress(const QVariant &) const;
        void SyncProgress(const QVariant &) const;
};


}
