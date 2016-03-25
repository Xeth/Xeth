#include "AddConfigCommand.hpp"


namespace  Xeth {


AddConfigCommand::AddConfigCommand(DataBase &database) :
    _database(database)
{}


QVariant AddConfigCommand::operator ()(const QVariantMap &request)
{
    if(!request.contains("name")||!request.contains("value"))
    {
        return QVariant::fromValue(false);
    }

    return operator()(request["name"].toString(), request["value"].toString());
}


QVariant AddConfigCommand::operator()(const QString &key, const QString &value)
{
    _database.getConfig().insert(key, value);
    return QVariant::fromValue(true);
}


}
