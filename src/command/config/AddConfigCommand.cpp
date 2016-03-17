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

    return QVariant::fromValue(_database.getConfig().insert(request["name"].toString().toStdString().c_str(), request["value"].toString()));
}


}
