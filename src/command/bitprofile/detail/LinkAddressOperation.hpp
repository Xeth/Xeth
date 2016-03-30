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
            Ethereum::Connector::Provider &,
            const BitProfile::ProfileDescriptor &,
            const QString &address,
            const QString &password,
            Notifier &
        );

        void operator()();

    private:
        BitProfile::ProfileAdministrator _admin;
        QString _address;
        QString _password;
        Notifier &_notifier;
};


}
