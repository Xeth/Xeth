#pragma once 

#include <QString>

#include "bitprofile/ProfileDescriptor.hpp"
#include "bitprofile/ProfileAdministrator.hpp"

#include "facade/Notifier.hpp"


namespace Xeth{


class LinkAddressOperation
{
    public:
        LinkAddressOperation
        (
            const BitProfile::ProfileAdministrator &,
            const QString &address,
            const QString &password,
            Notifier &
        );

        void operator()();

    private:
        void emitError(const char *);

    private:
        BitProfile::ProfileAdministrator _admin;
        QString _address;
        QString _password;
        Notifier &_notifier;
};


}
