#include "CopyToClipboardCommand.hpp"


namespace Xeth{


QVariant CopyToClipboardCommand::operator()(const QString &text)
{
    return copyText(text);
}


QVariant CopyToClipboardCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("mime")||!request.contains("value"))
    {
        return QVariant::fromValue(false);
    }

    QString mime = request["mime"].toString();

    if(mime=="text")
    {
        return copyText(request["value"].toString());
    }

    if(mime=="image")
    {
        return copyImage(request["value"].toString());
    }

    return QVariant::fromValue(false); //type unknown
}


QVariant CopyToClipboardCommand::copyText(const QString &text)
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text);

    return QVariant::fromValue(true);
}


QVariant CopyToClipboardCommand::copyImage(const QString &path)
{
    return QVariant::fromValue(false); //not implemented
}


}
