#pragma once 

#include <QObject>
#include <QVariant>
#include <QVariantMap>

#include "Notifier.hpp"
#include "Invoker.hpp"
#include "database/DataBase.hpp"

#include "command/bitprofile/CreateProfileCommand.hpp"
#include "command/bitprofile/EstimateProfileOperationCommand.hpp"
#include "command/bitprofile/LinkStealthAddressCommand.hpp"
#include "command/bitprofile/ListProfilesCommand.hpp"
#include "command/bitprofile/ListRegistrarsCommand.hpp"
#include "command/bitprofile/MoveProfileCommand.hpp"
#include "command/bitprofile/ResolvePaymentAddressCommand.hpp"
#include "command/bitprofile/ExportProfileCommand.hpp"


namespace Xeth{


class BitProfileFacade : public QObject
{
    Q_OBJECT
    public:
        BitProfileFacade(Ethereum::Connector::Provider &, DataBase &, Notifier &, const Settings &);

        Q_INVOKABLE QVariant createProfile(const QVariantMap &);
        Q_INVOKABLE QVariant listProfiles();
        Q_INVOKABLE QVariant listRegistrars(const QVariantMap &);
        Q_INVOKABLE QVariant estimate(const QVariantMap &);
        Q_INVOKABLE QVariant linkStealthAddress(const QVariantMap &);
        Q_INVOKABLE QVariant moveProfile(const QVariantMap &);
        Q_INVOKABLE QVariant resolvePaymentAddress(const QString &);
        Q_INVOKABLE QVariant exportProfile(const QVariantMap &);


    private:
        Ethereum::Connector::Provider &_provider;
        DataBase &_database;
        BitProfileStore &_store;
        Notifier &_notifier;
        const Settings &_settings;
        Invoker _invoker;
};


}
