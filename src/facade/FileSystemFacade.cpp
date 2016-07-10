#include "FileSystemFacade.hpp"


namespace Xeth{


FileSystemFacade::FileSystemFacade(Invoker<Notifier> &invoker) :
    _invoker(invoker)
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


QVariant FileSystemFacade::readImage(const QString &path)
{
    ReadImageCommand command;
    return _invoker.invoke(command, path);
}


}
