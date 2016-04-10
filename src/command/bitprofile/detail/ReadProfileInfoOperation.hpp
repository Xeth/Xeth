#pragma once

#include <QVariantMap>

#include "bitprofile/Profile.hpp"

#include "io/IpfsReader.hpp"
#include "io/IpfsNameRegistrar.hpp"
#include "conf/Settings.hpp"
#include "facade/Notifier.hpp"



namespace Xeth{


class ReadProfileInfoOperation
{
    public:
        ReadProfileInfoOperation
        (
            const BitProfile::Profile &,
            const Settings &,
            Notifier &notifier
        );

        void operator()();


    private:
        QString getProfileUri();
        void emitData(const QVariantMap &);
        void emitError(const char *);

    private:
        BitProfile::Profile _profile;
        const Settings &_settings;
        Notifier &_notifier;
};


}
