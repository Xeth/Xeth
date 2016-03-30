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
    if(op=="edit")
    {
        return estimateEdit(request);
    }
    else
    if(op=="move")
    {
        return estimateMove(request);
    }

    return QVariant::fromValue(false);
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

    return QString(_estimator.estimateRegister(registrar, request["name"].toString().toStdString()).str().c_str());
}


QVariant EstimateProfileOperationCommand::estimateEdit(const QVariantMap &request)
{
    if(!request.contains("key")||!request.contains("value")||!request.contains("uri"))
    {
        return QVariant::fromValue(false);
    }

    BitProfileStore::Iterator it = _store.find(request["uri"].toString());
    if(it==_store.end())
    {
        return QVariant::fromValue(false);
    }

    BitProfile::ProfileAdministrator admin = BitProfile::ProfileAdministrator::FromDescriptor(_provider, *it);

    std::string key = request["key"].toString().toStdString();
    std::string value = request["value"].toString().toStdString();

    return QString(_estimator.estimateEdit(admin, key, value).str().c_str());
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

    return QString(gas.str().c_str());
}


}
