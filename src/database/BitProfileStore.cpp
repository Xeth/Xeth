#include "BitProfileStore.hpp"


namespace Xeth{


BitProfileStore::BitProfileStore(BitProfile::Network net) :
    _store(net)
{}


BitProfileStore::Iterator BitProfileStore::begin() const
{
    return _store.begin();
}


BitProfileStore::Iterator BitProfileStore::end() const
{
    return _store.end();
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
