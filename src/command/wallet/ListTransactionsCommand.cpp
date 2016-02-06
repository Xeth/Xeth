#include "ListTransactionsCommand.hpp"


namespace Xeth{


ListTransactionsCommand::ListTransactionsCommand(DataBase &database) :
    _database(database)
{}


QVariant ListTransactionsCommand::operator ()(const QVariantMap &request)
{
    QJsonArray result;

    TransactionStore & store = _database.getTransactions();

    if(request.contains("limit"))
    {
        DataRange<TransactionStore> range(store);
        range.setLimit(request["limit"].toInt());

        if(request.contains("offset"))
        {
            range.setOffset(request["offset"].toInt());
        }

        for(DataRange<TransactionStore>::Iterator it = range.begin(), end = range.end(); it!=end; ++it)
        {
            result.push_back(*it);
        }

    }
    else
    {
        for(TransactionStore::Iterator  it = store.begin(), end = store.end(); it!=end; ++it)
        {
            result.push_back(*it);
        }
    }


    return QVariant::fromValue(result);
}


}
