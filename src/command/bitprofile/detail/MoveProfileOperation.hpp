#pragma once 

#include <QString>

#include "ethrpc/Provider.hpp"
#include "bitprofile/ProfileDescriptor.hpp"
#include "bitprofile/ProfileAdministrator.hpp"

#include "database/BitProfileStore.hpp"
#include "facade/Notifier.hpp"


namespace Xeth{


class MoveProfileOperation
{
    public:
        MoveProfileOperation
        (
            Ethereum::Connector::Provider &,
            BitProfileStore &store,
            const BitProfile::ProfileDescriptor &,
            const BitProfile::Registrar &,
            const QString &name,
            const QString &password,
            Notifier &
        );

        void operator()();

    private:
        BitProfile::ProfileAdministrator _admin;
        BitProfileStore &_store;
        BitProfile::Registrar _registrar;
        QString _name;
        QString _password;
        Notifier &_notifier;
};


}
