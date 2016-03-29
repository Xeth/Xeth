#pragma once

#include <QVariant>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonArray>

#include "bitprofile/ProfileStore.hpp"


namespace Xeth{


class ListProfilesCommand
{
    public:
        ListProfilesCommand(BitProfile::ProfileStore &);

        QVariant operator()();

    private:
        BitProfile::ProfileStore &_store;
};


}
