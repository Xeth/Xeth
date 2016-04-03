#include "ImportPresaleKeyCommand.hpp"

namespace Xeth{

ImportPresaleKeyCommand::ImportPresaleKeyCommand(const Settings &settings, Synchronizer &synchronizer) :
    _settings(settings),
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

    QProcess process;
    EthProcessInitializer::Initialize(process, _settings, args);

    process.start();
    process.waitForFinished();

    if(process.exitStatus() != 0)
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
