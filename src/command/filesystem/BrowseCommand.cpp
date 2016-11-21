#include "BrowseCommand.hpp"
#include <QDebug>

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
            QString extensions = request.contains("extensions")?request["extensions"].toString():"";
            return browseFile(caption, extensions);
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


QVariant BrowseCommand::browseFile(const QString &caption, QString &filter)
{
    return openFileDialog(caption, QFileDialog::ExistingFiles, filter);
}


QVariant BrowseCommand::browseNewFile(const QString &caption)
{
    return openFileDialog(caption, QFileDialog::AnyFile, "");
}


QVariant BrowseCommand::browseDirectory(const QString &caption)
{
    return openFileDialog(caption, QFileDialog::DirectoryOnly, "");
}


QString BrowseCommand::openFileDialog(const QString &caption, const QFileDialog::FileMode &mode, const QString &filter)
{
    QFileDialog dialog(NULL, caption);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setFileMode(mode);
    if(filter.size())
    {
        dialog.setNameFilter(filter);
    }
    dialog.setWindowModality(Qt::ApplicationModal);
    dialog.activateWindow();
    dialog.setFocus();
    dialog.setDirectory(QDir::homePath());
    if(dialog.exec())
    {
        return *dialog.selectedFiles().begin();
    }
    return "";
}




}
