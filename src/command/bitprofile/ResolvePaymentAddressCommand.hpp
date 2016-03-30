#pragma once 

#include <QVariant>
#include <QString>

#include "bitprofile/Resolver.hpp"
#include "bitprofile/Profile.hpp"

#include "env/Settings.hpp"
#include "env/GetBitProfileNetwork.hpp"


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
