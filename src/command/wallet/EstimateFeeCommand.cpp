#include "EstimateFeeCommand.hpp"

namespace Xeth{


EstimateFeeCommand::EstimateFeeCommand(Ethereum::Connector::Provider &provider) :
    _estimator(provider)
{}


QVariant EstimateFeeCommand::operator()(const QVariantMap &request)
{
    try
    {
        if(!request.contains("from")||!request.contains("to")||!request.contains("amount"))
        {
            return QVariant::fromValue(false);
        }
        QString from = request["from"].toString();
        QString to = request["to"].toString();
        BigInt amount = BigInt(request["amount"].toString().toStdString());
        BigInt price = _estimator.getGasPrice();
        if(request.contains("factor"))
        {
            size_t factor = request["factor"].toInt();
            if(factor==0)
            {
                price = 0;
            }
            else
            {
                price *= factor;
                price /= 100;
            }
        }

        QVariantMap result;

        BigInt fee = (to.length()<42) ? _estimator.estimate(from, to, amount) : _estimator.estimateStealth(from, to, amount);
        result["gas"] = fee.str().c_str();
        fee *= price;
        result["fee"] = fee.str().c_str();
        result["price"] = price.str().c_str();
        return result;
    }
    catch(...)
    {}
    return QVariant::fromValue(false);
}




}
