#include "ListTransactionsCommand.hpp"


namespace Xeth{


ListTransactionsCommand::ListTransactionsCommand(DataBase &database) :
    _database(database)
{}


QVariant ListTransactionsCommand::operator ()(const QVariantMap &request)
{
    size_t limit, offset;

    if(request.contains("limit"))
    {
        limit = request["limit"].toInt();
    }
    else
    {
        limit = 0;
    }

    if(request.contains("offset"))
    {
        offset = request["offset"].toInt();
    }
    else
    {
        offset = 0;
    }

    TransactionStore & store = _database.getTransactions();

    TransactionStore::Iterator it = offset ? store.at(offset) : store.begin();
    TransactionStore::Iterator end = store.end();

    QJsonArray result;

    if(limit)
    {
        for(;limit > 0 && it != end; limit--, ++it)
        {
            result.push_back(*it);
        }
    }
    else
    {
        for(;it != end; ++it)
        {
            result.push_back(*it);
        }
    }

    return QVariant::fromValue(result);
}


}
