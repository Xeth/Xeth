#pragma once

#include <QVariant>
#include <QVariantMap>
#include <QString>

#include "ethrpc/Provider.hpp"
#include "ethrpc/GasEstimator.hpp"

#include "types/BigInt.hpp"


namespace Xeth{


class EstimateFeeCommand
{
    public:
        EstimateFeeCommand(Ethereum::Connector::Provider &);
        QVariant operator()(const QVariantMap &);

    private:
        BigInt estimateStealthGas(const QString &from, const QString &to, const BigInt &);
        BigInt estimateGas(const QString &from, const QString &to, const BigInt &);

    private:
        Ethereum::Connector::GasEstimator _estimator;

};


}
