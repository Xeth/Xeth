#pragma once 


#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "bitprofile/ProfileDescriptor.hpp"

#include "database/BitProfileStore.hpp"
#include "facade/Notifier.hpp"

#include "detail/LinkAddressOperation.hpp"
#include "detail/BitProfileAction.hpp"


namespace Xeth{


class LinkStealthAddressCommand
{
    public:
        LinkStealthAddressCommand(Ethereum::Connector::Provider &, BitProfileStore &, Notifier &);

        QVariant operator()(const QVariantMap &);

    private:
        typedef BitProfileAction<LinkAddressOperation> LinkAddressAction;

    private:
        Ethereum::Connector::Provider &_provider;
        BitProfileStore &_store;
        Notifier &_notifier;
};


}
