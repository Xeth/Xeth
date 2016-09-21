#include "NetworkFacade.hpp"


namespace Xeth{


NetworkFacade::NetworkFacade(Ethereum::Connector::Provider &provider, Invoker<Notifier> &invoker) : 
    _provider(provider),
    _invoker(invoker)
{}



QVariant NetworkFacade::getPeersCount()
{
    GetPeersCountCommand command(_provider);
    return _invoker.invoke(command, NullCommandArguments());
}


QObject * NetworkFacade::getPeersCountAsync()
{
    GetPeersCountCommand command(_provider);
    return _invoker.invokeAsync(command, NullCommandArguments());
}



}
