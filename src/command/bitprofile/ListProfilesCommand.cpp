#include "ListProfilesCommand.hpp"


namespace Xeth{


ListProfilesCommand::ListProfilesCommand(BitProfile::ProfileStore &store) :
    _store(store)
{}


QVariant ListProfilesCommand::operator()()
{
    QJsonArray result;
    for(BitProfile::ProfileStore::Iterator it = _store.begin(), end = _store.end(); it!=end; ++it)
    {
        QJsonObject profile;
        BitProfile::ProfileDescriptor descriptor = *it;
        profile["name"] = descriptor.getName().c_str();
        profile["uri"] = descriptor.getURI().c_str();
        result.append(profile);
    }
    return result.toVariantList();
}


}
