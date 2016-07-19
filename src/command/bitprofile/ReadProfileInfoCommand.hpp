#pragma once 


#include <QVariant>
#include <QString>


#include "bitprofile/Profile.hpp"
#include "bitprofile/Resolver.hpp"

#include "conf/Settings.hpp"
#include "conf/GetBitProfileNetwork.hpp"
#include "io/IpfsReader.hpp"
#include "io/IpfsNameRegistrar.hpp"


namespace Xeth{



class ReadProfileInfoCommand
{
    public:
        ReadProfileInfoCommand(Ethereum::Connector::Provider &, const Settings &);
        QVariant operator()(const QString &);

    private:
        BitProfile::Resolver _resolver;
        const Settings &_settings;
};



}
