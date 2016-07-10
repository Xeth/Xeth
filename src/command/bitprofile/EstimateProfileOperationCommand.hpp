#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "ethrpc/Provider.hpp"
#include "bitprofile/GasEstimator.hpp"
#include "bitprofile/Resolver.hpp"

#include "conf/Settings.hpp"
#include "conf/GetBitProfileNetwork.hpp"
#include "database/BitProfileStore.hpp"
#include "types/BigInt.hpp"

namespace Xeth{


class EstimateProfileOperationCommand
{
    public:
        EstimateProfileOperationCommand(Ethereum::Connector::Provider &, BitProfileStore &, const Settings &);

        QVariant operator()(const QVariantMap &);

    private:
        QVariant makeFeeObject(const BigInt &gas, const QVariantMap &request);
        QVariant estimateStealthLink(const QVariantMap &);
        QVariant estimateRegister(const QVariantMap &);
        QVariant estimateEditDetails(const QVariantMap &);
        QVariant estimateMove(const QVariantMap &);
        BigInt estimateEdit(const QString &uri, const QString &key, const QString &value);

    private:
        Ethereum::Connector::Provider &_provider;
        BitProfileStore &_store;
        BitProfile::GasEstimator _estimator;
        BitProfile::Resolver _resolver;
};


}

