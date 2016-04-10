#pragma once

#include <QVariant>
#include <QVariantMap>

#include "bitprofile/MasterRegistrar.hpp"
#include "bitprofile/Resolver.hpp"

#include "facade/Notifier.hpp"
#include "database/BitProfileStore.hpp"
#include "conf/GetBitProfileNetwork.hpp"

#include "detail/BitProfileAction.hpp"
#include "detail/CreateProfileOperation.hpp"


namespace Xeth{


class CreateProfileCommand
{
    public:
        CreateProfileCommand(Ethereum::Connector::Provider &provider, BitProfileStore &store, const Settings &settings, Notifier &notifier);

        QVariant operator()(const QVariantMap &);

    private:
        typedef BitProfileAction<CreateProfileOperation> CreateProfileAction;

    private:
        BitProfile::Resolver _resolver;
        BitProfileStore &_store;
        Notifier &_notifier;
};


}
