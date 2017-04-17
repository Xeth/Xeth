#include <QStorageInfo>
#include "HddProbe.hpp"


namespace Xeth{


HddProbe::~HddProbe()
{}


bool HddProbe::operator()(const Settings &settings) const
{
    QStorageInfo storage = settings.has("datadir") ? QStorageInfo(settings.get("datadir")) : QStorageInfo::root();

    if(storage.isReadOnly())
    {
        emit Error("Read only device");
        return false;
    }

    qint64 freeSpace = storage.bytesFree() / 1048576;

    if( freeSpace < 50 )
    {
        emit Error("Not enough disk space");
        return false;
    }

    if( freeSpace < 1024 )
    {
        emit Warning("Low disk space");
        return false;
    }

    return true;
}





}
