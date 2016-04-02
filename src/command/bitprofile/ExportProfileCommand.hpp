#pragma once 

#include <QDir>
#include <QVariant>
#include <QString>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"

#include "bitprofile/ProfileAdministrator.hpp"
#include "bitprofile/ProfileDescriptor.hpp"

#include "database/DataBase.hpp"
#include "database/BitProfileStore.hpp"
#include "database/EthereumKeyStore.hpp"
#include "database/StealthKeyStore.hpp"

#include "io/JsonWriter.hpp"

namespace Xeth{


class ExportProfileCommand
{
    public:
        ExportProfileCommand(Ethereum::Connector::Provider &, DataBase &);

        QVariant operator()(const QVariantMap &);

    private:
        Ethereum::Connector::Provider &_provider;
        BitProfileStore &_bitprofiles;
        EthereumKeyStore &_ethereumKeys;
        StealthKeyStore &_stealthKeys;
};


}
