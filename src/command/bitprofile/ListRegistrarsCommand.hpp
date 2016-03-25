#pragma once 

#include <QVariant>
#include <QStringList>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "bitprofile/MasterRegistrar.hpp"

#include "env/Settings.hpp"

#include "detail/GetBitProfileNetwork.hpp"

namespace Xeth{


class ListRegistrarsCommand
{
    public:
        ListRegistrarsCommand(Ethereum::Connector::Provider &provider, const Settings &settings);

        QVariant operator()(const QVariantMap &request);


    private:
        template<class Iterator>
        QVariant makeList(Iterator, Iterator, size_t);


    private:
        Ethereum::Connector::Provider &_provider;
        const Settings &_settings;
};


}
