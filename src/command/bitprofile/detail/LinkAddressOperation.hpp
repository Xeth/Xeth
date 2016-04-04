#pragma once 

#include "ProfileOperation.hpp"


namespace Xeth{


class LinkAddressOperation : public ProfileOperation
{
    public:
        LinkAddressOperation
        (
            const BitProfile::ProfileAdministrator &,
            const QString &address,
            const QString &password,
            Notifier &
        );


    protected:
        void execute();

    private:
        QString _address;
};


}
