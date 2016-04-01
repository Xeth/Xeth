#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "bitprofile/GasEstimator.hpp"
#include "bitprofile/Resolver.hpp"

#include "env/Settings.hpp"
#include "env/GetBitProfileNetwork.hpp"
#include "database/BitProfileStore.hpp"
#include "types/BigInt.hpp"

namespace Xeth{


class EstimateProfileOperationCommand
{
    public:
        EstimateProfileOperationCommand(Ethereum::Connector::Provider &, BitProfileStore &, const Settings &);

        QVariant operator()(const QVariantMap &);

    private:
        QVariant estimateStealthLink(const QVariantMap &);
        QVariant estimateRegister(const QVariantMap &);
        QVariant estimateEdit(const QVariantMap &);
        QVariant estimateMove(const QVariantMap &);
        QVariant estimateEdit(const QString &uri, const QString &key, const QString &value);

    private:
        Ethereum::Connector::Provider &_provider;
        BitProfileStore &_store;
        BitProfile::GasEstimator _estimator;
        BitProfile::Resolver _resolver;
};


}

