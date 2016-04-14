#pragma once

#include <QVariant>
#include <QVariantMap>

#include "bitprofile/MasterRegistrar.hpp"
#include "bitprofile/Resolver.hpp"

#include "facade/Notifier.hpp"
#include "database/DataBase.hpp"
#include "conf/GetBitProfileNetwork.hpp"

#include "detail/BitProfileAction.hpp"
#include "detail/CreateProfileOperation.hpp"


namespace Xeth{


class CreateProfileCommand
{
    public:
        CreateProfileCommand(Ethereum::Connector::Provider &provider, DataBase &, const Settings &settings, Notifier &notifier);

        QVariant operator()(const QVariantMap &);

    private:
        typedef BitProfileAction<CreateProfileOperation> CreateProfileAction;

    private:
        BitProfile::Resolver _resolver;
        DataBase &_database;
        Notifier &_notifier;
};


}
