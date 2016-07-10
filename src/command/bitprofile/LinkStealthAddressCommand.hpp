#pragma once 


#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "bitprofile/ProfileDescriptor.hpp"
#include "bitprofile/ProfileAdministrator.hpp"


#include "database/BitProfileStore.hpp"
#include "types/BigInt.hpp"


namespace Xeth{


class LinkStealthAddressCommand
{
    public:
        LinkStealthAddressCommand(Ethereum::Connector::Provider &, BitProfileStore &);
        QVariant operator()(const QVariantMap &);

    private:
        Ethereum::Connector::Provider &_provider;
        BitProfileStore &_store;
};


}
