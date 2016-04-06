#pragma once 


#include <QVariant>
#include <QString>


#include "bitprofile/Profile.hpp"
#include "bitprofile/Resolver.hpp"


#include "facade/Notifier.hpp"
#include "env/Settings.hpp"
#include "env/GetBitProfileNetwork.hpp"


#include "detail/BitProfileAction.hpp"
#include "detail/ReadProfileInfoOperation.hpp"



namespace Xeth{



class ReadProfileInfoCommand
{
    public:
        ReadProfileInfoCommand(Ethereum::Connector::Provider &, const Settings &, Notifier &);

        QVariant operator()(const QString &);

    private:
        typedef BitProfileAction<ReadProfileInfoOperation> ReadProfileInfoAction;

    private:
        BitProfile::Resolver _resolver;
        const Settings &_settings;
        Notifier &_notifier;

};



}
