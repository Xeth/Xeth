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
            BitProfileStore &store,
            const BitProfile::ProfileAdministrator &,
            const BitProfile::Registrar &,
            const QString &name,
            const QString &password,
            const BigInt &gas,
            Notifier &
        );

        void operator()();

    private:
        void emitError(const char *);

    private:
        BitProfile::ProfileAdministrator _admin;
        BitProfileStore &_store;
        BitProfile::Registrar _registrar;
        QString _name;
        QString _password;
        BigInt _gas;
        Notifier &_notifier;
        BitProfile::Profile::URI _uri;
};


}
