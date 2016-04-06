#pragma once

#include <QVariant>
#include <QVariantMap>
#include <QString>

#include "ethrpc/Provider.hpp"


#include "types/BigInt.hpp"
#include "detail/SendGasEstimator.hpp"


namespace Xeth{


class EstimateFeeCommand
{
    public:
        EstimateFeeCommand(Ethereum::Connector::Provider &);
        QVariant operator()(const QVariantMap &);

    private:
        SendGasEstimator _estimator;

};


}
