#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "bitprofile/Resolver.hpp"
#include "bitprofile/Registrar.hpp"
#include "bitprofile/ProfileDescriptor.hpp"

#include "database/BitProfileStore.hpp"
#include "facade/Notifier.hpp"
#include "env/Settings.hpp"
#include "env/GetBitProfileNetwork.hpp"

#include "detail/BitProfileAction.hpp"
#include "detail/MoveProfileOperation.hpp"


namespace Xeth{


class MoveProfileCommand
{
    public:
        MoveProfileCommand(Ethereum::Connector::Provider &, BitProfileStore &, const Settings &, Notifier &);

        QVariant operator()(const QVariantMap &);

    private:
        typedef BitProfileAction<MoveProfileOperation> MoveProfileAction;

    private:
        Ethereum::Connector::Provider &_provider;
        BitProfileStore &_store;
        const Settings &_settings;
        Notifier &_notifier;
};


}
