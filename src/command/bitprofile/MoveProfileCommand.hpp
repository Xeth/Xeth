#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "bitprofile/Resolver.hpp"
#include "bitprofile/Registrar.hpp"
#include "bitprofile/ProfileDescriptor.hpp"
#include "bitprofile/ProfileAdministrator.hpp"

#include "database/BitProfileStore.hpp"
#include "conf/Settings.hpp"
#include "conf/GetBitProfileNetwork.hpp"
#include "types/BigInt.hpp"


namespace Xeth{


class MoveProfileCommand
{
    public:
        MoveProfileCommand(Ethereum::Connector::Provider &, BitProfileStore &, const Settings &);

        QVariant operator()(const QVariantMap &);

    private:
        Ethereum::Connector::Provider &_provider;
        BitProfileStore &_store;
        const Settings &_settings;
};


}
