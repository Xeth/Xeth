#include "EstimateProfileOperationCommand.hpp"


namespace Xeth{


EstimateProfileOperationCommand::EstimateProfileOperationCommand(Ethereum::Connector::Provider &provider, BitProfileStore &store, const Settings &settings) :
    _provider(provider),
    _store(store),
    _estimator(provider),
    _resolver(provider, GetBitprofileNetwork(settings))
{}


QVariant EstimateProfileOperationCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("operation"))
    {
        return QVariant::fromValue(false);
    }

    QString op = request["operation"].toString();

    if(op=="register")
    {
        return estimateRegister(request);
    }
    else
    if(op=="stealth")
    {
        return estimateStealthLink(request);
    }
    else
    if(op=="edit")
    {
        return estimateEditDetails(request);
    }
    else
    if(op=="move")
    {
        return estimateMove(request);
    }
    else
    {
        return QVariant::fromValue(false);
    }
}


QVariant EstimateProfileOperationCommand::makeFeeObject(const BigInt &gas, const QVariantMap &request)
{
    Ethereum::Connector::GasEstimator estimator(_provider);
    BigInt price = estimator.getPrice();
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

    BigInt fee = gas * price;
    result["gas"] = gas.str().c_str();
    result["fee"] = fee.str().c_str();
    result["price"] = price.str().c_str();
    return result;
}


QVariant EstimateProfileOperationCommand::estimateRegister(const QVariantMap &request)
{
    if(!request.contains("name")||!request.contains("context"))
    {
        return QVariant::fromValue(false);
    }

    BitProfile::Registrar registrar = _resolver.lookupRegistrar(request["context"].toString().toStdString());
    if(registrar.isNull())
    {
        return QVariant::fromValue(false);
    }

    return makeFeeObject(_estimator.estimateRegister(registrar, request["name"].toString().toStdString()), request);
}

QVariant EstimateProfileOperationCommand::estimateStealthLink(const QVariantMap &request)
{
    if(!request.contains("uri"))
    {
        return makeFeeObject(BigInt(136000), request);
    }
    else
    {
        return makeFeeObject(estimateEdit(request["uri"].toString(), "payments", request["address"].toString()), request);
    }
}


QVariant EstimateProfileOperationCommand::estimateEditDetails(const QVariantMap &request)
{
    if(!request.contains("uri"))
    {
        return makeFeeObject(BigInt(136000), request);
    }

    return makeFeeObject(estimateEdit(request["uri"].toString(), "details", "ipfs://QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"), request);
}

BigInt EstimateProfileOperationCommand::estimateEdit(const QString &uri, const QString &key, const QString &value)
{
    BitProfileStore::Iterator it = _store.find(uri);
    if(it==_store.end())
    {
        return BigInt(0);
    }

    BitProfile::ProfileAdministrator admin = BitProfile::ProfileAdministrator::FromDescriptor(_provider, *it);

    return _estimator.estimateEdit(admin, key.toStdString(), value.toStdString());
}

QVariant EstimateProfileOperationCommand::estimateMove(const QVariantMap &request)
{
    if(!request.contains("uri")||!request.contains("name")||!request.contains("context"))
    {
        return QVariant::fromValue(false);
    }

    BitProfileStore::Iterator it = _store.find(request["uri"].toString());
    if(it==_store.end())
    {
        return QVariant::fromValue(false);
    }
    BitProfile::ProfileAdministrator admin = BitProfile::ProfileAdministrator::FromDescriptor(_provider, *it);

    BitProfile::Registrar registrar = _resolver.lookupRegistrar(request["context"].toString().toStdString());
    if(registrar.isNull())
    {
        return QVariant::fromValue(false);
    }


    BigInt gas = _estimator.estimateUnlink(_resolver.lookupRegistrar(admin.getProfile().getURI().getContext()), admin);
    gas += _estimator.estimateLink(registrar, admin, request["name"].toString().toStdString());

    return makeFeeObject(gas, request);
}


}
