#pragma once 

#include <QString>

#include "bitprofile/ProfileDescriptor.hpp"
#include "bitprofile/ProfileAdministrator.hpp"

#include "facade/Notifier.hpp"


namespace Xeth{


class ProfileOperation
{
    public:
        ProfileOperation
        (
            const BitProfile::ProfileAdministrator &,
            const QString &password,
            Notifier &
        );

        void operator()();


    protected:
        virtual void execute() = 0;
        void emitError(const char *);
        void emitData(const QString &key, const QVariant &);
        QString getProfileUri();

    protected:
        BitProfile::ProfileAdministrator _admin;
        QString _password;
        Notifier &_notifier;
};


}
