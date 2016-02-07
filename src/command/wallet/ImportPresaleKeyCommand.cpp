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
        result["error"] = "Invalid arguments";
        return QVariant::fromValue(result);
    }

    QStringList args;
    args.push_back("--password");
    args.push_back(password);
    args.push_back("wallet");
    args.push_back("import");
    args.push_back(path);

    _process.exec(args);
    _process.waitForFinished();

    result["output"] = _process.readAll();

    if(_process.exitStatus() != 0)
    {
        result["error"] = "Import failed";
    }
    else
    {
        JsonReader reader;
        Json::Value json;
        if(!reader.read(path.toStdString().c_str(), json))
        {
            result["error"] = "invalid json";
        }
        else
        {
            _synchronizer.watchAddress(json["ethaddr"].asString());
        }
    }

    return QVariant::fromValue(result);

}


}
