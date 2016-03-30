#include "LinkStealthAddressCommand.hpp"


namespace Xeth{


LinkStealthAddressCommand::LinkStealthAddressCommand(Ethereum::Connector::Provider &provider, BitProfileStore &store, Notifier &notifier) :
    _provider(provider),
    _store(store),
    _notifier(notifier)
{}


QVariant LinkStealthAddressCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("uri")||!request.contains("address"))
    {
        return QVariant::fromValue(false);
    }

    BitProfileStore::Iterator it = _store.find(request["uri"].toString());
    if(it==_store.end())
    {
        return QVariant::fromValue(false);
    }

    BitProfile::ProfileAdministrator admin = BitProfile::ProfileAdministrator::FromDescriptor(_provider, *it);

    if(request.contains("price"))
    {
        admin.setGasPrice(BigInt(request["price"].toString().toStdString()));
    }

    LinkAddressAction * action = LinkAddressAction::Create(LinkAddressOperation
    (
        admin, 
        request["address"].toString(),
        request["password"].toString(),
        _notifier
    ));

    action->start();
    return QVariant::fromValue(true);

}


}
