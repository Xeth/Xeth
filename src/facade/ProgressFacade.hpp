#pragma once 

#include <QObject>

#include "synchronizer/Synchronizer.hpp"
#include "Notifier.hpp"
#include "command/Invoker.hpp"


namespace Xeth{


class ProgressFacade : public QObject
{
    Q_OBJECT
    public:
        ProgressFacade(Synchronizer &, Invoker<Notifier> &);

        Q_INVOKABLE QVariant getScan() const;
        Q_INVOKABLE QVariant getSync() const;

    signals:
        void Scan(const QVariant &) const;
        void Sync(const QVariant &) const;

    private slots:
        void emitScanProgress(double);
        void emitSyncProgress(double);

    private:
        Synchronizer &_synchronizer;
};


}
