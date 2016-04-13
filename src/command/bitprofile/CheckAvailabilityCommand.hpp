#pragma once

#include <QString>
#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "bitprofile/Resolver.hpp"

#include "conf/Settings.hpp"
#include "conf/GetBitProfileNetwork.hpp"


namespace Xeth{



class CheckAvailabilityCommand
{
    public:
        CheckAvailabilityCommand(Ethereum::Connector::Provider &provider, const Settings &);


        QVariant operator()(const QString &);
        QVariant operator()(const QVariantMap &);

    private:
        BitProfile::Resolver _resolver;

};


}
