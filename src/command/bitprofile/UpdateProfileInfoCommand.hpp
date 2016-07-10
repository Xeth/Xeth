#pragma once 


#include <QVariant>
#include <QBuffer>
#include <QImage>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "bitprofile/ProfileDescriptor.hpp"
#include "bitprofile/ProfileAdministrator.hpp"

#include "database/BitProfileStore.hpp"
#include "conf/Settings.hpp"
#include "io/IpfsReader.hpp"
#include "io/IpfsNameRegistrar.hpp"
#include "io/IpfsWriter.hpp"
#include "types/BigInt.hpp"



namespace Xeth{


class UpdateProfileInfoCommand
{
    public:
        UpdateProfileInfoCommand(Ethereum::Connector::Provider &, BitProfileStore &, const Settings &);
        QVariant operator()(const QVariantMap &);

    private:
        Ethereum::Connector::Provider &_provider;
        BitProfileStore &_store;
        const Settings &_settings;
};


}
