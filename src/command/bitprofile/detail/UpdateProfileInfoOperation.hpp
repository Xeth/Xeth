#pragma once

#include <QVariantMap>
#include <QImage>
#include <QByteArray>
#include <QBuffer>

#include "io/IpfsWriter.hpp"
#include "io/IpfsReader.hpp"
#include "io/IpfsNameRegistrar.hpp"
#include "env/Settings.hpp"

#include "ProfileOperation.hpp"


namespace Xeth{


class UpdateProfileInfoOperation : public ProfileOperation
{
    public:
        UpdateProfileInfoOperation
        (
            const BitProfile::ProfileAdministrator &, 
            const QString &password, 
            const Settings &,
            const QVariantMap &,
            bool useIpns,
            Notifier &notifier
        );


    protected:
        void execute();


    private:
        const Settings &_settings;
        QVariantMap _details;
        bool _ipns;
};


}
