#include "ExportKeyCommand.hpp"

namespace Xeth{

ExportKeyCommand::ExportKeyCommand(const Settings &settings ) :
    _settings(settings)
{}


QVariant ExportKeyCommand::operator ()(const QVariantMap &request)
{

    QString address = request["address"].toString();
    QString destinationPath = request["destination"].toString();

    if(!address.length() || !destinationPath.length())
    {
        return QVariant::fromValue(false);
    }


    QString path = _settings.get("attach", "");

    if(!path.length())
    {
        Ethereum::Connector::DefaultGethPath defaultPath;
        path = defaultPath.toString().c_str();
    }

    path += QDir::separator();
    path += "keystore";

    QDirIterator it(path);

    while(it.hasNext())
    {
        QString fileName = it.next();
        if(fileName == "."|| fileName == "..")
        {
            continue;
        }

        QFile file;
        file.setFileName(fileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        QJsonDocument document;
        document.fromJson(file.readAll());

        QJsonObject object = document.object();

        QString keyAddress = object.value("address").toString();

        if(address == keyAddress)
        {
            QString destinationFile = destinationPath;
            destinationFile +=  QDir::separator();
            destinationFile += fileName;

            QString sourceFile = path;
            sourceFile +=  QDir::separator();
            sourceFile += fileName;

            return QVariant::fromValue(QFile::copy(sourceFile, destinationFile));
        }

    }

    return QVariant::fromValue(false);



}


}
