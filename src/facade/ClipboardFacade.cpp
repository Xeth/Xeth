#include "ClipboardFacade.hpp"


namespace Xeth{


ClipboardFacade::ClipboardFacade(Invoker<Notifier> &invoker) :
    _invoker(invoker)
{}


QVariant ClipboardFacade::getText()
{
    GetFromClipboardCommand command;
    return _invoker.invoke(command, NullCommandArguments());
}


QVariant ClipboardFacade::setText(const QString &text)
{
    CopyToClipboardCommand command;
    return _invoker.invoke(command, text);
}

}
