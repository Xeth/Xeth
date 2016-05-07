#include "LinkStealthAddressCommand.hpp"


namespace Xeth{


LinkStealthAddressCommand::LinkStealthAddressCommand(Ethereum::Connector::Provider &provider, BitProfileStore &store) :
    _provider(provider),
    _store(store)
{}


QVariant LinkStealthAddressCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("uri")||!request.contains("stealth")||!request.contains("password"))
    {
        return QVariant::fromValue(false);
    }

    BitProfileStore::Iterator it = _store.find(request["uri"].toString());
    if(it==_store.end())
    {
        return QVariant::fromValue(false);
    }

    BitProfile::ProfileAdministrator admin = BitProfile::ProfileAdministrator::FromDescriptor(_provider, *it);

    admin.setGasPrice(BigInt(request.contains("price") ? request["price"].toString().toStdString(): "0"));
    admin.setGasLimit(BigInt(request.contains("gas") ? request["gas"].toString().toStdString() : "0"));

    if(!admin.setPaymentAddress(request["stealth"].toString().toStdString(), request["password"].toString().toStdString()))
    {
        return QVariant::fromValue(false);
    }

    return QVariant::fromValue(true);

}


}
