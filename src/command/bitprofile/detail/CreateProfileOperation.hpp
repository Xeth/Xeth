#pragma once 

#include <QString>
#include <QJsonObject>

#include "bitprofile/ProfileAdministrator.hpp"
#include "bitprofile/Registrar.hpp"
#include "bitprofile/ProfileStore.hpp"

#include "facade/Notifier.hpp"
#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"

#include "detail/StealthSpendKeyRedeemer.hpp"


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
            DataBase &,
            Synchronizer &,
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
        DataBase &_database;
        Synchronizer &_synchronizer;
        Notifier &_notifier;
};


}
