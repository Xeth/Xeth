#include "ListProfilesCommand.hpp"


namespace Xeth{


ListProfilesCommand::ListProfilesCommand(BitProfileStore &store) :
    _store(store)
{}


QVariant ListProfilesCommand::operator()()
{
    QJsonArray result;
    for(BitProfileStore::Iterator it = _store.begin(), end = _store.end(); it!=end; ++it)
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
