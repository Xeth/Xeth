#include "ClipboardFacade.hpp"


namespace Xeth{


ClipboardFacade::ClipboardFacade(Notifier &notifier) :
    _invoker(notifier)
{}


QVariant ClipboardFacade::get()
{
    GetFromClipboardCommand command;
    return _invoker.invoke(command, NullCommandArguments());
}


QVariant ClipboardFacade::set(const QString &text)
{
    CopyToClipboardCommand command;
    return _invoker.invoke(command, text);
}

}
