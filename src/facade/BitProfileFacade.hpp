#pragma once 

#include <QObject>
#include <QVariant>
#include <QVariantMap>

#include "Notifier.hpp"

#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"

#include "command/Invoker.hpp"
#include "command/bitprofile/CreateProfileCommand.hpp"
#include "command/bitprofile/EstimateProfileOperationCommand.hpp"
#include "command/bitprofile/LinkStealthAddressCommand.hpp"
#include "command/bitprofile/ListProfilesCommand.hpp"
#include "command/bitprofile/ListRegistrarsCommand.hpp"
#include "command/bitprofile/MoveProfileCommand.hpp"
#include "command/bitprofile/ResolvePaymentAddressCommand.hpp"
#include "command/bitprofile/ExportProfileCommand.hpp"
#include "command/bitprofile/ImportProfileCommand.hpp"
#include "command/bitprofile/GetProfileDataCommand.hpp"
#include "command/bitprofile/UpdateProfileInfoCommand.hpp"
#include "command/bitprofile/ReadProfileInfoCommand.hpp"
#include "command/bitprofile/CheckAvailabilityCommand.hpp"
#include "command/bitprofile/ValidateIdCommand.hpp"


namespace Xeth{


class BitProfileFacade : public QObject
{
    Q_OBJECT
    public:
        BitProfileFacade(Ethereum::Connector::Provider &, DataBase &, Synchronizer &, Notifier &, const Settings &, Invoker<Notifier> &);

        Q_INVOKABLE QVariant listProfiles();
        Q_INVOKABLE QVariant listRegistrars(const QVariantMap &);
        Q_INVOKABLE QVariant estimate(const QVariantMap &);
        Q_INVOKABLE QVariant resolvePaymentAddress(const QString &);
        Q_INVOKABLE QVariant exportProfile(const QVariantMap &);
        Q_INVOKABLE QVariant importProfile(const QString &);
        Q_INVOKABLE QVariant getData(const QVariantMap &);
        Q_INVOKABLE QVariant isIdAvailable(const QString &);
        Q_INVOKABLE QVariant isIdAvailable(const QVariantMap &);
        Q_INVOKABLE QVariant isIdValid(const QString &);

        Q_INVOKABLE QObject * createProfileAsync(const QVariantMap &);
        Q_INVOKABLE QObject * linkStealthAddressAsync(const QVariantMap &);
        Q_INVOKABLE QObject * moveProfileAsync(const QVariantMap &);
        Q_INVOKABLE QObject * updateDetailsAsync(const QVariantMap &);
        Q_INVOKABLE QObject * getDetailsAsync(const QString &);

    signals:
        void Profile(const QVariantMap &) const;
        void Renamed(const QVariantMap &) const;

    private slots:
        void emitProfile(const BitProfile::ProfileDescriptor &);
        void emitProfileRename(const QString &old, const BitProfile::ProfileDescriptor &);

    private:
        Ethereum::Connector::Provider &_provider;
        DataBase &_database;
        Synchronizer &_synchronizer;
        BitProfileStore &_store;
        Notifier &_notifier;
        const Settings &_settings;
        Invoker<Notifier> &_invoker;
};


}
