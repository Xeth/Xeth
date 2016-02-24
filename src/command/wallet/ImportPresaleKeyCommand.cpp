#include "ImportPresaleKeyCommand.hpp"

namespace Xeth{

ImportPresaleKeyCommand::ImportPresaleKeyCommand(const Settings &settings, Synchronizer &synchronizer) :
    _process(settings),
    _synchronizer(synchronizer)
{}


bool ImportPresaleKeyCommand::import(const QString &path, const QString &password, QString &address)
{

    QStringList args;
    Json::Value json;

    args.push_back("--password");
    args.push_back(password);
    args.push_back("wallet");
    args.push_back("import");
    args.push_back(path);

    _process.exec(args);
    _process.waitForFinished();

    _process.readAll();

    if(_process.exitStatus() != 0)
    {
        return false;
    }
    else
    {
        JsonReader reader;

        if(!reader.read(path.toStdString().c_str(), json))
        {
            return false;
        }
        else
        {
            std::string addr = json["ethaddr"].asString();
            _synchronizer.watchAddress(addr);
            address = addr.c_str();
        }
    }

    return true;
}


bool ImportPresaleKeyCommand::import(const QVariantMap &request, QString &address)
{
    if(!request.contains("file")||!request.contains("password"))
    {
        return false;
    }

    return import(request["file"].toString(),  request["password"].toString(), address);
}


QVariant ImportPresaleKeyCommand::operator ()(const QVariantMap &request)
{
    QString address;
    if(!import(request, address))
    {
        return QVariant::fromValue(false);
    }
    return QVariant::fromValue(address);
}


}
