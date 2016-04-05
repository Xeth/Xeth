#include "BrowseCommand.hpp"


namespace Xeth{

QVariant BrowseCommand::operator()()
{
    return browseDirectory("");
}

QVariant BrowseCommand::operator()(const QVariantMap &request)
{
    QString caption = request.contains("caption") ? request["caption"].toString() : "";
    if(request.contains("type"))
    {
        QString type = request["type"].toString();

        if(type == "save")
        {
            return browseNewFile(caption);
        }
        else
        if(type=="open")
        {
            return browseFile(caption, request.contains("extensions")?request["extensions"].toString():"");
        }
        else
        if(type=="directory")
        {
            return browseDirectory(caption);
        }
        else
        {
            return QVariant::fromValue(false); //type not known
        }
    }
    return browseDirectory(caption);
}


QVariant BrowseCommand::browseFile(const QString &caption, const QString &extensions)
{
    return QVariant::fromValue(QFileDialog::getOpenFileName(NULL, caption, QDir::currentPath(), extensions));
}


QVariant BrowseCommand::browseNewFile(const QString &caption)
{
    return QVariant::fromValue(QFileDialog::getSaveFileName(NULL, caption));
}


QVariant BrowseCommand::browseDirectory(const QString &caption)
{
    return QVariant::fromValue(QFileDialog::getExistingDirectory(NULL, caption));
}


}
