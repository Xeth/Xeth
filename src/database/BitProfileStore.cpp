#include "BitProfileStore.hpp"


namespace Xeth{


BitProfileStore::BitProfileStore(BitProfile::Network net) :
    _store(net)
{
    qRegisterMetaType<BitProfile::ProfileDescriptor>("BitProfile::ProfileDescriptor");
}


BitProfileStore::Iterator BitProfileStore::find(const QString &uri) const
{
    return _store.find(uri.toStdString());
}

BitProfileStore::Iterator BitProfileStore::find(const char *uri) const
{
    return _store.find(uri);
}

BitProfileStore::Iterator BitProfileStore::begin() const
{
    return _store.begin();
}


BitProfileStore::Iterator BitProfileStore::end() const
{
    return _store.end();
}

bool BitProfileStore::rename(const BitProfile::Profile::URI &old, const BitProfile::Profile::URI &uri)
{
    if(_store.changeProfileURI(old, uri))
    {
        emit Renamed(QString(old.toString().c_str()), QString(uri.toString().c_str()));
        return true;
    }
    return false;
}


bool BitProfileStore::insert(const BitProfile::ProfileDescriptor &descriptor)
{
    if(_store.insert(descriptor))
    {
        emit NewItem(descriptor);
        return true;
    }

    return false;
}


bool BitProfileStore::remove(const BitProfile::Profile::URI &uri)
{
    if(_store.remove(uri))
    {
        emit Removed(QString(uri.toString().c_str()));
        return true;
    }
    return false;
}


bool BitProfileStore::remove(const QString &uri)
{
    if(_store.remove(uri.toStdString()))
    {
        emit Removed(uri);
        return true;
    }
    return false;
}


}
