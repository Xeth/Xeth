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

    LinkAddressAction * action = LinkAddressAction::Create(LinkAddressOperation
    (
        _provider, 
        *it,
        request["address"].toString(),
        request["password"].toString(),
        _notifier
    ));

    action->start();
    return QVariant::fromValue(true);

}


}
