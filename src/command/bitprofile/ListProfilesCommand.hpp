#pragma once

#include <QVariant>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonArray>

#include "database/BitProfileStore.hpp"


namespace Xeth{


class ListProfilesCommand
{
    public:
        ListProfilesCommand(BitProfileStore &);

        QVariant operator()();

    private:
        BitProfileStore &_store;
};


}
