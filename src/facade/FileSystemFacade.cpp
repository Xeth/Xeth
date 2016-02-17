#include "FileSystemFacade.hpp"


namespace Xeth{


FileSystemFacade::FileSystemFacade(Notifier &notifier) :
    _invoker(notifier)
{}


QVariant FileSystemFacade::browse(const QVariantMap &request)
{
    BrowseCommand command;
    return _invoker.invoke(command, request);
}


QVariant FileSystemFacade::browse()
{
    BrowseCommand command;
    return _invoker.invoke(command, NullCommandArguments());
}


}
