#pragma once

#include <QVariant>
#include <QVariantMap>

#include "bitprofile/MasterRegistrar.hpp"
#include "bitprofile/Resolver.hpp"
#include "bitprofile/ProfileAdministrator.hpp"
#include "bitprofile/Registrar.hpp"

#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"
#include "conf/GetBitProfileNetwork.hpp"

#include "detail/StealthSpendKeyRedeemer.hpp"


namespace Xeth{



class CreateProfileCommand
{
    public:
        CreateProfileCommand(Ethereum::Connector::Provider &, DataBase &, Synchronizer &, const Settings &);
        QVariant operator()(const QVariantMap &);

    private:
        BitProfile::Resolver _resolver;
        DataBase &_database;
        Synchronizer &_synchronizer;
};


}
