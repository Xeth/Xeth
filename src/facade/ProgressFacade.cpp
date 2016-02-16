#include "ProgressFacade.hpp"
#include <QDebug>

namespace Xeth{


ProgressFacade::ProgressFacade(Synchronizer &synchronizer, Notifier &notifier) :
    _synchronizer(synchronizer)
{}


QVariant ProgressFacade::getScan() const
{
    qDebug()<<"fetching scan progress";
    return QVariant::fromValue(_synchronizer.getScanProgress());
}


QVariant ProgressFacade::getSync() const
{
    qDebug()<<"fetching sync progress..";
    return QVariant::fromValue(_synchronizer.getChainProgress());
}



}
