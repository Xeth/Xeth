#pragma once 

#include <QString>
#include <QJsonObject>

#include "bitprofile/ProfileAdministrator.hpp"
#include "bitprofile/Registrar.hpp"
#include "bitprofile/ProfileStore.hpp"

#include "facade/Notifier.hpp"


namespace Xeth{


class CreateProfileOperation
{
    public:
        CreateProfileOperation
        (
            const BitProfile::Registrar &,
            const QString &name,
            const QString &account,
            const QString &password,
            BitProfileStore &,
            Notifier &
        );

        void operator()();

    private:
        void emitError(const char *);

    private:
        BitProfile::Registrar _registrar;
        QString _name;
        QString _account;
        QString _password;
        BitProfileStore &_store;
        Notifier &_notifier;
};


}
