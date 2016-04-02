#pragma once

#include <QString>
#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "bitprofile/ProfileDescriptor.hpp"
#include "bitprofile/Profile.hpp"

#include "database/BitProfileStore.hpp"
#include "database/EthereumKeyStore.hpp"
#include "database/StealthKeyStore.hpp"
#include "database/DataBase.hpp"


namespace Xeth{


class ImportProfileCommand
{
    public:
        ImportProfileCommand(Ethereum::Connector::Provider &, DataBase &);

        QVariant operator()(const QString &);
        QVariant operator()(const QVariantMap &);

    private:
        QVariant importProfileData(const QString &, bool includeKeys=true);

        template<class Serializer, class KeyStore>
        void importKeys(const Json::Value &keys, const Serializer &serializer, KeyStore &store);

    private:
        Ethereum::Connector::Provider &_provider;
        BitProfileStore &_bitprofiles;
        StealthKeyStore &_stealthKeys;
        EthereumKeyStore &_ethereumKeys;
};


}
