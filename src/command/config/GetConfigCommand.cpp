#include "GetConfigCommand.hpp"


namespace Xeth{


GetConfigCommand::GetConfigCommand(DataBase &database):
    _database(database)
{}


QVariant GetConfigCommand::operator ()(const QString &name)
{
    return QVariant::fromValue(QString(_database.getConfig().get(name.toStdString().c_str())));
}



}
