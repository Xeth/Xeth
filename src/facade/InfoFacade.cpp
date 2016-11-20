
#include "InfoFacade.hpp"

namespace Xeth{


InfoFacade::InfoFacade(const Settings &settings,  Invoker<Notifier>  &invoker) : 
    _settings(settings),
    _invoker(invoker)
{}


QString InfoFacade::getVersion() const
{
    return QString(XETH_VERSION);
}


QVariant InfoFacade::getClientVersion() const
{
    GetClientVersionCommand command(_settings);
    return _invoker.invoke(command, NullCommandArguments());
}


QVariant InfoFacade::getClientVersionNumber() const
{
    GetClientVersionCommand command(_settings);
    return _invoker.invoke(command, GetClientVersionCommand::Version_Only);
}

QVariant InfoFacade::getLatestReleaseInfo() const
{
    GetLastReleaseInfoCommand command;
    return _invoker.invoke(command, NullCommandArguments());
}


Q_INVOKABLE QObject * InfoFacade::getLatestReleaseInfoAsync() const
{
    GetLastReleaseInfoCommand command;
    return _invoker.invokeAsync(command, NullCommandArguments());
}

}
