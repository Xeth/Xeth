#pragma once 

#include <QVariant>
#include <QString>

#include "bitprofile/Resolver.hpp"
#include "bitprofile/Profile.hpp"

#include "conf/Settings.hpp"
#include "conf/GetBitProfileNetwork.hpp"


namespace Xeth{


class ResolvePaymentAddressCommand 
{
    public:
        ResolvePaymentAddressCommand(Ethereum::Connector::Provider &, const Settings &);

        QVariant operator()(const QString &);

    private:
        BitProfile::Resolver _resolver;
};


}
