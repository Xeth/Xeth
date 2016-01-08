#include "GetTransactionCommand.hpp"


namespace Xeth{


GetTransactionCommand::GetTransactionCommand(DataBase &database) :
    _database(database)
{}


QVariant GetTransactionCommand::operator ()(const QString &hash)
{
    return operator ()(hash.toStdString().c_str());
}


QVariant GetTransactionCommand::operator ()(const char *hash)
{
    return QVariant::fromValue(_database.getTransactions().get(hash));
}



}
