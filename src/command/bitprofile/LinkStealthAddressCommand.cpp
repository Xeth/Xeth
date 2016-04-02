#include "LinkStealthAddressCommand.hpp"


namespace Xeth{


LinkStealthAddressCommand::LinkStealthAddressCommand(Ethereum::Connector::Provider &provider, BitProfileStore &store, Notifier &notifier) :
    _provider(provider),
    _store(store),
    _notifier(notifier)
{}


QVariant LinkStealthAddressCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("uri")||!request.contains("stealth"))
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

    LinkAddressAction * action = LinkAddressAction::Create(LinkAddressOperation
    (
        admin, 
        request["stealth"].toString(),
        request["password"].toString(),
        _notifier
    ));

    action->start();
    return QVariant::fromValue(true);

}


}
