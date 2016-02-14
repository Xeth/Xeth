#include "Notifier.hpp"

namespace Xeth{


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
    emit Transaction(tx);
}


void Notifier::emitScanProgress(double progress)
{
    emit ScanProgress(QVariant::fromValue(progress));
}


void Notifier::emitSyncProgress(double progress)
{
    emit SyncProgress(QVariant::fromValue(progress));
}


}
