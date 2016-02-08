#include "ImportPresaleKeyCommand.hpp"

namespace Xeth{

ImportPresaleKeyCommand::ImportPresaleKeyCommand(const Settings &settings, Synchronizer &synchronizer) :
    _process(settings),
    _synchronizer(synchronizer)
{}

QVariant ImportPresaleKeyCommand::operator ()(const QVariantMap &request)
{
    QString path = request["path"].toString();
    QString password = request["password"].toString();

    QVariantMap result;

    if(!path.length() || !password.length())
    {
        return QVariant::fromValue(false);
    }

    QStringList args;
    Json::Value json;
    std::string address;

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
        return QVariant::fromValue(false);
    }
    else
    {
        JsonReader reader;

        if(!reader.read(path.toStdString().c_str(), json))
        {
            return QVariant::fromValue(false);
        }
        else
        {
            address = json["ethaddr"].asString();
            _synchronizer.watchAddress(address);
        }
    }

    return QVariant::fromValue(QString(address.c_str()));

}


}
