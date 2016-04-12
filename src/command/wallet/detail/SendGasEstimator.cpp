#include "SendGasEstimator.hpp"

namespace Xeth{


SendGasEstimator::SendGasEstimator(Ethereum::Connector::Provider &provider) :
    _estimator(provider)
{}


BigInt SendGasEstimator::estimate(const QString &from, const QString &to, const BigInt &amount)
{
    return estimate(from.toStdString(), to.toStdString(), amount);
}


BigInt SendGasEstimator::estimate(const std::string &from, const std::string &to, const BigInt &amount)
{
    return (to.length()<43) ? estimateHex(from, to, amount) : estimateStealth(from, to, amount);
}


BigInt SendGasEstimator::estimateHex(const QString &from, const QString &to, const BigInt &amount)
{
    return estimateHex(from.toStdString(), to.toStdString(), amount);
}


BigInt SendGasEstimator::estimateHex(const std::string &from, const std::string &, const BigInt &amount)
{
    return _estimator.estimate(from.c_str(), "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", amount);
}


BigInt SendGasEstimator::estimateStealth(const QString &from, const QString &to, const BigInt &amount)
{
    return estimateStealth(from.toStdString(), amount);
}


BigInt SendGasEstimator::estimateStealth(const std::string &from, const std::string &, const BigInt &amount)
{
    return estimateStealth(from, amount);
}


BigInt SendGasEstimator::estimateStealth(const std::string &from, const BigInt &amount)
{
    return  _estimator.estimate(from.c_str(), "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", amount, "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
}


BigInt SendGasEstimator::getGasPrice()
{
    return _estimator.getPrice();
}




StealthSendGasEstimator::StealthSendGasEstimator(Ethereum::Connector::Provider &provider) : 
    _estimator(provider)
{}


BigInt StealthSendGasEstimator::estimate(const QString &from, const QString &, const BigInt &amount)
{
    return _estimator.estimateStealth(from.toStdString(), amount);
}


BigInt StealthSendGasEstimator::estimate(const std::string &from, const std::string &, const BigInt &amount)
{
    return _estimator.estimateStealth(from, amount);
}


BigInt StealthSendGasEstimator::getGasPrice()
{
    return _estimator.getGasPrice();
}



HexSendGasEstimator::HexSendGasEstimator(Ethereum::Connector::Provider &provider) : 
    _estimator(provider)
{}


BigInt HexSendGasEstimator::estimate(const QString &from, const QString &to, const BigInt &amount)
{
    return _estimator.estimateHex(from.toStdString(), to.toStdString(), amount);
}


BigInt HexSendGasEstimator::estimate(const std::string &from, const std::string &to, const BigInt &amount)
{
    return _estimator.estimateHex(from, to, amount);
}


BigInt HexSendGasEstimator::getGasPrice()
{
    return _estimator.getGasPrice();
}


}
