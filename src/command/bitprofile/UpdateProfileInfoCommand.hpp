#pragma once 


#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "bitprofile/ProfileDescriptor.hpp"

#include "database/BitProfileStore.hpp"
#include "facade/Notifier.hpp"

#include "detail/UpdateProfileInfoOperation.hpp"
#include "detail/BitProfileAction.hpp"


namespace Xeth{


class UpdateProfileInfoCommand
{
    public:
        UpdateProfileInfoCommand(Ethereum::Connector::Provider &, BitProfileStore &, Notifier &, const Settings &);

        QVariant operator()(const QVariantMap &);

    private:
        typedef BitProfileAction<UpdateProfileInfoOperation> UpdateProfileInfoAction;

    private:
        Ethereum::Connector::Provider &_provider;
        BitProfileStore &_store;
        Notifier &_notifier;
        const Settings &_settings;
};


}
